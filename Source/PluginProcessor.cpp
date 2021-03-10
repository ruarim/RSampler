/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
RSampler1AudioProcessor::RSampler1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), valueTree(*this, nullptr, "Parameters", createParams())
#endif
{
    rFormatManager.registerBasicFormats();

    for (int i = 0; i < rVoices; i++)
    {
        rSampler.addVoice(new juce::SamplerVoice);
    }
}

RSampler1AudioProcessor::~RSampler1AudioProcessor()
{
    rFormatReader = nullptr;
}

//==============================================================================
const juce::String RSampler1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RSampler1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RSampler1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RSampler1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RSampler1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RSampler1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RSampler1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void RSampler1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RSampler1AudioProcessor::getProgramName (int index)
{
    return {};
}

void RSampler1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RSampler1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    lastSampleRate = sampleRate;

    rSampler.setCurrentPlaybackSampleRate(sampleRate);

    //create current spec
    juce::dsp::ProcessSpec spec; 
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();

    //make sure filter doesnt contain irrelevant values
    stateVariableFilter.reset();
    //setup filter 
    updateFilter();
    stateVariableFilter.prepare(spec);
}
void RSampler1AudioProcessor::updateFilter()
{
    int fChoice = *valueTree.getRawParameterValue("FCHOICE");
    float freq = *valueTree.getRawParameterValue("CUTOFF");
    switch (fChoice)
    {
    case 0: //lowpass
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        break;
    case 1: //bandpass
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        break;
    case 2: //highpass
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        break;
    }
    stateVariableFilter.state->setCutOffFrequency(lastSampleRate, *valueTree.getRawParameterValue("CUTOFF"), *valueTree.getRawParameterValue("RESO"));
    
}
void RSampler1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RSampler1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void RSampler1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = buffer.getNumSamples();
    
    //apply env to each voice
    for (int i = 0; i < rSampler.getNumVoices(); i++)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(rSampler.getSound(i).get()))
        {
            ADSRParams.attack = *valueTree.getRawParameterValue("ATTACK");
            ADSRParams.decay = *valueTree.getRawParameterValue("DECAY");
            ADSRParams.sustain = *valueTree.getRawParameterValue("SUSTAIN");
            ADSRParams.release = *valueTree.getRawParameterValue("RELEASE");
            
            sound->setEnvelopeParameters(ADSRParams);
        }
    }

    

    rSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);

    updateFilter();

    stateVariableFilter.process(juce::dsp::ProcessContextReplacing<float>(block));

    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = channelData[sample] * *valueTree.getRawParameterValue("GAIN");
        }
    }

    
}

//==============================================================================
bool RSampler1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RSampler1AudioProcessor::createEditor()
{
    return new RSampler1AudioProcessorEditor (*this);
}

//==============================================================================
void RSampler1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RSampler1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
void RSampler1AudioProcessor::loadFile(int midiNote) //takes midi note to load sample for
{
    juce::FileChooser chooser{ "PLEASE LOAD FILE." };

    if (chooser.browseForFileToOpen())
    {
        //might not check if audio file
        auto file = chooser.getResult();
        rFormatReader = rFormatManager.createReaderFor(file);

    }
    //72 - 80 midinotes for pad sampler style
    juce::BigInteger range;
    //0 - 128 for full pitch range
    range.setRange(midiNote, 1, true);
    
    rSampler.addSound(new juce::SamplerSound("Sample", *rFormatReader, range, midiNote, 0.1, 0.1, 10)); //after range; ATTACK, RELEASE, MAXLENGTH
}
juce::AudioProcessorValueTreeState::ParameterLayout RSampler1AudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>(0.0f, 5.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>(0.0f, 5.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>(0.0f, 5.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF", "Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f), 2000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RESO", "Resonance", juce::NormalisableRange<float>(0.1f, 10.0f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FCHOICE", "FilterChoice", juce::NormalisableRange<float>(0, 2), 0));
    return{ params.begin(), params.end() }; //returns parameters list
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RSampler1AudioProcessor();
}


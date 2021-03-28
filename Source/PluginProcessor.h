/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class RSampler1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    RSampler1AudioProcessor();
    ~RSampler1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState valueTree;
    juce::AudioBuffer<float> getWaveform() { return waveform; }

    void loadFile();
    void loadFileDragDrop(const juce::String& path);
    void updateFilter();

private:
    juce::Synthesiser rSampler;
    const int rVoices = 4;
    

    juce::AudioFormatManager rFormatManager;
    juce::AudioFormatReader* rFormatReader{ nullptr };

    double lastSampleRate;
    //use process duplcator to use mono dsp effect on both channels
    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;

    juce::ADSR::Parameters ADSRParams;
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    juce::AudioBuffer<float> waveform;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RSampler1AudioProcessor)
};

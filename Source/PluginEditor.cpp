/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RSampler1AudioProcessorEditor::RSampler1AudioProcessorEditor (RSampler1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), envGUI(p), gainGUI(p), filterGUI(p), reverbGUI(p)
{
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&gainGUI);
    addAndMakeVisible(&filterGUI); 
    addAndMakeVisible(&reverbGUI);

    setSize(400, 460);
}

RSampler1AudioProcessorEditor::~RSampler1AudioProcessorEditor()
{
}

//==============================================================================
void RSampler1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto waveform = audioProcessor.getWaveform();
    if (waveform.getNumChannels() == 1) //if sample is loaded 
    { //paint waveform
        g.setColour(juce::Colours::white);
        g.strokePath(displayWaveform(), juce::PathStrokeType(2));

    }
    else
    {
        //const juce::String text = "Drag and drop sample.";
        g.setColour(juce::Colours::white);
        //g.drawText(&text, width, height, juce::Justification::centred, false);
        g.drawRoundedRectangle(10.0f, 10.0f, 380.0f, 100.0f, 5.0f, 1.0f);
    }
}

void RSampler1AudioProcessorEditor::resized()
{   
    //lay out components
    envGUI.setBounds(0, 125, 400, 150);
    gainGUI.setBounds(getWidth() / 2 + 110, 125, 100, 150);
    filterGUI.setBounds(getWidth() / 2 - 10, 125, 130, 150);
    reverbGUI.setBounds(10, 275, 400, 300);

}

bool RSampler1AudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    //check if dropped file is valid type 
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}

void RSampler1AudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    
    for (auto file : files)
    {
           //if file valid, load in processor
        if (isInterestedInFileDrag(files))
        {
            //load sound
            audioProcessor.loadFileDragDrop(file);

        }
    }
    repaint();
}

juce::Path RSampler1AudioProcessorEditor::displayWaveform()
{
    int width = 400;
    int height = 125;
    auto waveform = audioProcessor.getWaveform();
    auto scaleRatio = waveform.getNumSamples() / width; //scale lenght of sample to x axis
    auto buffer = waveform.getReadPointer(0); //

    juce::Path p;
    p.clear();
    for (int sample = 0; sample < waveform.getNumSamples(); sample += scaleRatio) 
    {
        audioPoints.push_back(buffer[sample]); 
    }
    p.startNewSubPath(-10, width); //set start point for drawing

    for (int sample = 0; sample < audioPoints.size(); ++sample)
    {
        auto point  = juce::jmap<float>(audioPoints[sample], -1, 1.0f, height, 0); //scales input on y axis, convert -1 to 1 values to fit y axis //offset by 50 to move position on GUI

        p.lineTo(sample, point);
    }

    waveform.clear(); //clear old data
    audioPoints.clear();

    return(p);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RSampler1AudioProcessorEditor::RSampler1AudioProcessorEditor (RSampler1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), envGUI(p), gainGUI(p), filterGUI(p)
{
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&gainGUI);
    addAndMakeVisible(&filterGUI);

    //try catch!! 
    
    //sample1Button.onClick = [&]() { audioProcessor.loadFile(); };  //c
    //addAndMakeVisible(sample1Button);

    setSize(420, 300);
}

RSampler1AudioProcessorEditor::~RSampler1AudioProcessorEditor()
{
}

//==============================================================================
void RSampler1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    if (paintWaveform)
    {
        g.setColour(juce::Colours::white);
        g.strokePath(displayWaveform(), juce::PathStrokeType(2));

        paintWaveform = false;
    }
}

void RSampler1AudioProcessorEditor::resized()
{   
    //lay out components
    envGUI.setBounds(0, getHeight() / 2, 400, 150);
    gainGUI.setBounds(getWidth() / 2 + 90, getHeight() / 2, 100, 150);
    filterGUI.setBounds(getWidth() / 2 - 30, getHeight() / 2, 130, 150);

    sample1Button.setBounds(10, 10, 400, 100); //c
}

bool RSampler1AudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    //check corrected file tpy 
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3"))
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
           //file relevant load to in processor
        if (isInterestedInFileDrag(files))
        {
            paintWaveform = true;
            //load sound
            audioProcessor.loadFileDragDrop(file);

        }
    }
    repaint();
}

juce::Path RSampler1AudioProcessorEditor::displayWaveform()
{
    int height = 450;
    int width = 200;
    int offset = 45;
    auto waveform = audioProcessor.getWaveform();
    auto scaleRatio = waveform.getNumSamples() / height; //scale lenght of sample to x axis
    auto buffer = waveform.getReadPointer(0); //

    juce::Path p;
    p.clear();
    
    for (int sample = 0; sample < waveform.getNumSamples(); sample += scaleRatio) 
    {
        audioPoints.push_back(buffer[sample]); 
    }
    p.startNewSubPath(0, height); //set start point for drawing

    for (int sample = 0; sample < audioPoints.size(); ++sample)
    {
        auto point  = juce::jmap<float>(audioPoints[sample], -1, 1.0f, width, 0) - offset; //scales input on y axis, convert -1 to 1 values to fit y axis //offset by 50 to move position on GUI

        p.lineTo(sample, point);
    }

    waveform.clear(); //clear old data
    audioPoints.clear();

    return(p);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Gain.h"
#include "Filter.h"

//==============================================================================
/**
*/
class RSampler1AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public juce::FileDragAndDropTarget
{
public:
    RSampler1AudioProcessorEditor (RSampler1AudioProcessor&);
    ~RSampler1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    juce::Path displayWaveform();

private:
    Envelope envGUI;
    Gain gainGUI;
    Filter filterGUI;

    juce::TextButton sample1Button{ "LOAD SAMPLE" };

    std::vector<float> audioPoints;
    bool paintWaveform = false;
    // This reference is provided as a quick way for the editor to
    // access the processor object that created it.
    RSampler1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RSampler1AudioProcessorEditor)
};

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
class RSampler1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RSampler1AudioProcessorEditor (RSampler1AudioProcessor&);
    ~RSampler1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Envelope envGUI;
    Gain gainGUI;
    Filter filterGUI;

    juce::TextButton sample1Button{ "LOAD SAMPLE \n KEY: C" };
    juce::TextButton sample2Button{ "LOAD SAMPLE \n KEY: C#" };
    juce::TextButton sample3Button{ "LOAD SAMPLE \n KEY: D" };
    juce::TextButton sample4Button{ "LOAD SAMPLE \n KEY: D#" };
    juce::TextButton sample5Button{ "LOAD SAMPLE \n KEY: E" };
    juce::TextButton sample6Button{ "LOAD SAMPLE \n KEY: E#" };
    //juce::TextButton sample7Button{ "LOAD SAMPLE \n KEY: F" };
    //juce::TextButton sample8Button{ "LOAD SAMPLE \n KEY: F#" };
    //juce::TextButton sample9Button{ "LOAD SAMPLE \n KEY: G" };
    //juce::TextButton loadButton{ "LOAD SAMPLE" };
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RSampler1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RSampler1AudioProcessorEditor)
};

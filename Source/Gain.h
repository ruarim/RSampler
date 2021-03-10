/*
  ==============================================================================

    gain.h
    Created: 2 Mar 2021 12:20:21am
    Author:  Ruari

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class Gain : public juce::Component
{
public:
    Gain(RSampler1AudioProcessor& p);
    ~Gain();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RSampler1AudioProcessor& processor;

    juce::Slider gainSlider;

    juce::Label gainLabel{ {}, "Gain" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainVal;

    //int const sliderWidth = 40.0f;
};

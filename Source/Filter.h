/*
  ==============================================================================

    Filter.h
    Created: 2 Mar 2021 3:08:41pm
    Author:  Ruari

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class Filter : public juce::Component
{
public:
    Filter(RSampler1AudioProcessor& p);
    ~Filter();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RSampler1AudioProcessor& processor;

    juce::Slider cutoffSlider;
    juce::Slider resoSlider;
    juce::ComboBox filterCombo;

    juce::Label cutoffLabel{ {}, "Cutoff" };
    juce::Label resoLabel{ {}, "Reso" };
    juce::Label typeLabel{ {}, "Filter type" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resoVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterType;

    int const sliderWidth = 70.0f;
};
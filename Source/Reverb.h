/*
  ==============================================================================

    Reverb.h
    Created: 1 Mar 2021 11:24:20pm
    Author:  Ruari

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class Reverb : public juce::Component
{
public:
    Reverb(RSampler1AudioProcessor& p);
    ~Reverb();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RSampler1AudioProcessor& processor;

    juce::Slider drySlider;
    juce::Slider wetSlider;
    juce::Slider sizeSlider;
    juce::Slider widthSlider;

    juce::Label dryLabel{ {}, "Dry" };
    juce::Label wetLabel{ {}, "Wet" };
    juce::Label sizeLabel{ {}, "Room Size" };
    juce::Label widthLabel{ {}, "Width" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthVal;

    int const verticalSliderWidth = 40.0f;
    int const horizontalSliderWidth = 275.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Reverb)
};

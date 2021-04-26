/*
  ==============================================================================

    gain.cpp
    Created: 2 Mar 2021 12:20:21am
    Author:  Ruari

  ==============================================================================
*/

#include "Gain.h"
Gain::Gain(RSampler1AudioProcessor& p) :
    processor(p)
{
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setRange(0.0f, 5.0f);
    gainSlider.setValue(1.0f);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&gainSlider);
    addAndMakeVisible(&gainLabel);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    gainVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "GAIN", gainSlider);
}
Gain::~Gain()
{
    gainVal = nullptr;
}
void Gain::paint(juce::Graphics& g)
{

}

void Gain::resized()
{
    gainSlider.setBounds(10, 30, 70, 100);
}
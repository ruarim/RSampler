/*
  ==============================================================================

    Filter.cpp
    Created: 2 Mar 2021 3:08:41pm
    Author:  Ruari

  ==============================================================================
*/

#include "Filter.h"
Filter::Filter(RSampler1AudioProcessor& p) :
    processor(p)
{
    filterCombo.setJustificationType(juce::Justification::centred);
    filterCombo.addItem("LowPass", 1);
    filterCombo.addItem("BandPass", 2);
    filterCombo.addItem("HighPass", 3);
    addAndMakeVisible(&filterCombo);

    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutoffSlider.setRange(20.0f, 20000.0f);
    cutoffSlider.setValue(20.0f);
    cutoffSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&cutoffSlider);
    addAndMakeVisible(&cutoffLabel);
    cutoffLabel.attachToComponent(&cutoffSlider, false);
    cutoffLabel.setJustificationType(juce::Justification::centred);
    cutoffLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    resoSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    resoSlider.setValue(0.1f);
    resoSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&resoSlider);
    addAndMakeVisible(&resoLabel);
    resoLabel.attachToComponent(&resoSlider, false);
    resoLabel.setJustificationType(juce::Justification::centred);
    resoLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    cutoffSlider.setSkewFactorFromMidPoint(800.0f);

    cutoffVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "CUTOFF", cutoffSlider);
    resoVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "RESO", resoSlider);
    filterType = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.valueTree, "FCHOICE", filterCombo);
}
Filter::~Filter()
{
    cutoffVal = nullptr;
    resoVal = nullptr;
    filterType = nullptr;
}
void Filter::paint(juce::Graphics& g)
{

}

void Filter::resized()
{
    cutoffSlider.setBounds(0, 30, sliderWidth, 100);
    resoSlider.setBounds(60, 30, sliderWidth, 100);
    filterCombo.setBounds(15, 120, 100, 25);
}

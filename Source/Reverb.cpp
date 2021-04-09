/*
  ==============================================================================

    Reverb.cpp
    Created: 9 Apr 2021 12:56:15am
    Author:  Ruari

  ==============================================================================
*/

#include "Reverb.h"
#include <JuceHeader.h>

Reverb::Reverb(RSampler1AudioProcessor& p) :
    processor(p)
{
    //setSize(200, 300);

    drySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    drySlider.setRange(0.0f, 1.0f);
    drySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&drySlider);
    addAndMakeVisible(&dryLabel);
    dryLabel.attachToComponent(&drySlider, false);
 
    dryLabel.setJustificationType(juce::Justification::centred);
    dryLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    wetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    wetSlider.setRange(0.0f, 1.0f);
    wetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&wetSlider);
    addAndMakeVisible(&wetLabel);

    wetLabel.attachToComponent(&wetSlider, false);
    wetLabel.setJustificationType(juce::Justification::centred);
    wetLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    sizeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    sizeSlider.setRange(0.0f, 1.0f);
    sizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sizeSlider);
    addAndMakeVisible(&sizeLabel);

    sizeLabel.attachToComponent(&sizeSlider, false);
    sizeLabel.setJustificationType(juce::Justification::centred);
    sizeLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    widthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    widthSlider.setRange(0.0f, 1.0f);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&widthSlider);
    addAndMakeVisible(&widthLabel);

    widthLabel.attachToComponent(&widthSlider, false);
    widthLabel.setJustificationType(juce::Justification::centred);
    widthLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    dryVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "REVERBDRY", drySlider);
    wetVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "REVERBWET", wetSlider);
    sizeVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "REVERBSIZE", sizeSlider);
    widthVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "REVERBWIDTH", widthSlider);
}

Reverb::~Reverb()
{
    dryVal = nullptr;
    wetVal = nullptr;
    sizeVal = nullptr;
    widthVal = nullptr;
}

void Reverb::paint(juce::Graphics& g)
{

}

void Reverb::resized()
{
    drySlider.setBounds(10, 30, verticalSliderWidth, 150);
    wetSlider.setBounds(50, 30, verticalSliderWidth, 150);
    sizeSlider.setBounds(100, 50, horizontalSliderWidth, 30);
    widthSlider.setBounds(100, 125, horizontalSliderWidth, 30);
}
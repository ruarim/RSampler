/*
  ==============================================================================

    Envelope.cpp
    Created: 1 Mar 2021 11:24:20pm
    Author:  Ruari

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Envelope.h"

Envelope::Envelope(RSampler1AudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(&attackLabel);
    attackLabel.attachToComponent(&attackSlider, false);
    //attackLabel.setText("A", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    attackLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.0f, 5.0f);
    decaySlider.setValue(1.0f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(&decayLabel);
    //decayLabel.setText("D", juce::dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);
    addAndMakeVisible(&sustainLabel);
    //sustainLabel.setText("S", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);
    sustainLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);
    addAndMakeVisible(&releaseLabel);
    //releaseLabel.setText("R", juce::dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setFont(juce::Font(12.0f, juce::Font::plain));

    attackVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "ATTACK", attackSlider);
    decayVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "DECAY", decaySlider);
    sustainVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "SUSTAIN", sustainSlider);
    releaseVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.valueTree, "RELEASE", releaseSlider);
}

Envelope::~Envelope()
{
    attackVal = nullptr;
    decayVal = nullptr;
    sustainVal = nullptr;
    releaseVal = nullptr;
}

void Envelope::paint(juce::Graphics& g)
{

}

void Envelope::resized()
{
    attackSlider.setBounds(20, 30, sliderWidth, 100);
    decaySlider.setBounds(60, 30, sliderWidth, 100);
    sustainSlider.setBounds(100, 30, sliderWidth, 100);
    releaseSlider.setBounds(140, 30, sliderWidth, 100);
}


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
    sample1Button.onClick = [&]() { audioProcessor.loadFile(72); };  //c
    addAndMakeVisible(sample1Button);
    sample2Button.onClick = [&]() { audioProcessor.loadFile(73); }; //c#
    addAndMakeVisible(sample2Button);
    sample3Button.onClick = [&]() { audioProcessor.loadFile(74); }; //d
    addAndMakeVisible(sample3Button);
    sample4Button.onClick = [&]() { audioProcessor.loadFile(75); }; //d#
    addAndMakeVisible(sample4Button);
    sample5Button.onClick = [&]() { audioProcessor.loadFile(76); }; //e
    addAndMakeVisible(sample5Button);  
    sample6Button.onClick = [&]() { audioProcessor.loadFile(77); }; //e#
    addAndMakeVisible(sample6Button);
    //sample7Button.onClick = [&]() { audioProcessor.loadFile(78); }; //f
    //addAndMakeVisible(sample7Button); 
    //sample8Button.onClick = [&]() { audioProcessor.loadFile(79); }; //f#
    //addAndMakeVisible(sample8Button);
    //sample9Button.onClick = [&]() { audioProcessor.loadFile(80); }; //g
    //addAndMakeVisible(sample9Button);
    setSize(500, 300);
}

RSampler1AudioProcessorEditor::~RSampler1AudioProcessorEditor()
{
}

//==============================================================================
void RSampler1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    
}

void RSampler1AudioProcessorEditor::resized()
{   
    envGUI.setBounds(getWidth() / 2 - 250, getHeight() / 2, 400, 200);
    gainGUI.setBounds(getWidth() / 2 - 250, getHeight() / 2 - 150, 400, 200);
    filterGUI.setBounds(getWidth() / 2 - 180, getHeight() / 2 - 150, 400, 200);

    sample1Button.setBounds(getWidth() - 300, getHeight() - 100, 100, 100); //c
    sample2Button.setBounds(getWidth() - 200, getHeight() - 100, 100, 100); //c#
    sample3Button.setBounds(getWidth() - 100, getHeight() - 100, 100, 100); //d
    sample4Button.setBounds(getWidth() - 300, getHeight() - 200, 100, 100); //d#
    sample5Button.setBounds(getWidth() - 200, getHeight() - 200, 100, 100); //e
    sample6Button.setBounds(getWidth() - 100, getHeight() - 200, 100, 100); //e#
    //sample7Button.setBounds(getWidth() - 300, getHeight() - 300, 100, 100); //f
    //sample8Button.setBounds(getWidth() - 200, getHeight() - 300, 100, 100); //f#
    //sample9Button.setBounds(getWidth() - 100, getHeight() - 300, 100, 100); //g
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

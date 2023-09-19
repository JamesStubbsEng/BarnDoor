/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BarnDoorAudioProcessorEditor::BarnDoorAudioProcessorEditor (BarnDoorAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    addAndMakeVisible(polarPlot);
    setSize(600, 450);
}

BarnDoorAudioProcessorEditor::~BarnDoorAudioProcessorEditor()
{
}

//==============================================================================
void BarnDoorAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void BarnDoorAudioProcessorEditor::resized()
{
    polarPlot.centreWithSize(400, 400);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/PolarPlot.h"

//==============================================================================
/**
*/
class BarnDoorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BarnDoorAudioProcessorEditor (BarnDoorAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~BarnDoorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BarnDoorAudioProcessor& audioProcessor;

    AudioProcessorValueTreeState& valueTreeState;

    PolarPlot polarPlot;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarnDoorAudioProcessorEditor)
};

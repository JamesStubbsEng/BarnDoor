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

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    Slider wideningFactorSlider;
    Label wideningFactorLabel;
    std::unique_ptr<SliderAttachment> wideningFactorSliderAttachment;
    
    Slider wideningDriveSlider;
    Label wideningDriveLabel;
    std::unique_ptr<SliderAttachment> wideningDriveSliderAttachment;

    Slider wideningSpaceSlider;
    Label wideningSpaceLabel;
    std::unique_ptr<SliderAttachment> wideningSpaceSliderAttachment;

    Slider haasDelaySlider;
    Label haasDelayLabel;
    std::unique_ptr<SliderAttachment> haasDelaySliderAttachment;

    Slider haasColorSlider;
    Label haasColorLabel;
    std::unique_ptr<SliderAttachment> haasColorSliderAttachment;

    Slider haasBalanceSlider;
    Label haasBalanceLabel;
    std::unique_ptr<SliderAttachment> haasBalanceSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarnDoorAudioProcessorEditor)
};

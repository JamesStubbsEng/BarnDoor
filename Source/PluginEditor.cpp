/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BarnDoorAudioProcessorEditor::BarnDoorAudioProcessorEditor (BarnDoorAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts), polarPlot(p)
{
    addAndMakeVisible(polarPlot);

    wideningFactorSlider.setSliderStyle(juce::Slider::Rotary);
    wideningFactorSlider.setScrollWheelEnabled(false);
    wideningFactorSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wideningFactorSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    wideningFactorLabel.setText("Widening Factor", NotificationType::dontSendNotification);
    wideningFactorLabel.attachToComponent(&wideningFactorSlider, false);
    addAndMakeVisible(wideningFactorSlider);
    wideningFactorSliderAttachment.reset(new SliderAttachment(valueTreeState, "wideningFactor", wideningFactorSlider));

    wideningGainSlider.setSliderStyle(juce::Slider::Rotary);
    wideningGainSlider.setScrollWheelEnabled(false);
    wideningGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wideningGainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    wideningGainLabel.setText("Widening Gain", NotificationType::dontSendNotification);
    wideningGainLabel.attachToComponent(&wideningGainSlider, false);
    addAndMakeVisible(wideningGainSlider);
    wideningGainSliderAttachment.reset(new SliderAttachment(valueTreeState, "wideningGain", wideningGainSlider));

    setSize(700, 520);
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
    auto availableArea = getBounds().reduced(20);

    auto polarPlotWidthAndHeight = availableArea.getHeight() / 2;
    auto polarPlotArea = availableArea.removeFromTop(polarPlotWidthAndHeight);
    polarPlotArea.setWidth(polarPlotWidthAndHeight);
    polarPlotArea.translate((availableArea.getWidth() - polarPlotWidthAndHeight) / 2, 0);
    polarPlot.setBounds(polarPlotArea);
    
    auto sliderWidth = availableArea.getWidth() /2;
    auto sliderHeight = availableArea.getHeight();

    auto firstRow = availableArea.removeFromTop(sliderHeight);
    wideningFactorSlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));
    wideningGainSlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));
}

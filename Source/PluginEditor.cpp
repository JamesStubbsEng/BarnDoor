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

    wideningDriveSlider.setSliderStyle(juce::Slider::Rotary);
    wideningDriveSlider.setScrollWheelEnabled(false);
    wideningDriveSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wideningDriveSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    wideningDriveLabel.setText("Widening Drive", NotificationType::dontSendNotification);
    wideningDriveLabel.attachToComponent(&wideningDriveSlider, false);
    addAndMakeVisible(wideningDriveSlider);
    wideningDriveSliderAttachment.reset(new SliderAttachment(valueTreeState, "wideningDrive", wideningDriveSlider));


    haasDelaySlider.setSliderStyle(juce::Slider::Rotary);
    haasDelaySlider.setScrollWheelEnabled(false);
    haasDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    haasDelaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    haasDelayLabel.setText("Haas Delay", NotificationType::dontSendNotification);
    haasDelayLabel.attachToComponent(&haasDelaySlider, false);
    addAndMakeVisible(haasDelaySlider);
    haasDelaySliderAttachment.reset(new SliderAttachment(valueTreeState, "haasDelayTime", haasDelaySlider));

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

    auto polarPlotWidthAndHeight = availableArea.getHeight() / 3;
    auto polarPlotArea = availableArea.removeFromTop(polarPlotWidthAndHeight);
    polarPlotArea.setWidth(polarPlotWidthAndHeight);
    polarPlotArea.translate((availableArea.getWidth() - polarPlotWidthAndHeight) / 2, 0);
    polarPlot.setBounds(polarPlotArea);
    
    auto sliderWidth = availableArea.getWidth() /2;
    auto sliderHeight = availableArea.getHeight() / 2;

    auto firstRow = availableArea.removeFromTop(sliderHeight);
    haasDelaySlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));

    auto secondRow = availableArea.removeFromTop(sliderHeight);
    wideningDriveSlider.setBounds(secondRow.removeFromLeft(sliderWidth).reduced(30));
    wideningFactorSlider.setBounds(secondRow.removeFromLeft(sliderWidth).reduced(30));  
}

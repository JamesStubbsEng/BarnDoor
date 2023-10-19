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

    wideningSpaceSlider.setSliderStyle(juce::Slider::Rotary);
    wideningSpaceSlider.setScrollWheelEnabled(false);
    wideningSpaceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wideningSpaceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    wideningSpaceLabel.setText("Widening Space", NotificationType::dontSendNotification);
    wideningSpaceLabel.attachToComponent(&wideningSpaceSlider, false);
    addAndMakeVisible(wideningSpaceSlider);
    wideningSpaceSliderAttachment.reset(new SliderAttachment(valueTreeState, "wideningSpace", wideningSpaceSlider));


    haasDelaySlider.setSliderStyle(juce::Slider::Rotary);
    haasDelaySlider.setScrollWheelEnabled(false);
    haasDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    haasDelaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    haasDelayLabel.setText("Haas Delay", NotificationType::dontSendNotification);
    haasDelayLabel.attachToComponent(&haasDelaySlider, false);
    addAndMakeVisible(haasDelaySlider);
    haasDelaySliderAttachment.reset(new SliderAttachment(valueTreeState, "haasDelayTime", haasDelaySlider));

    haasColorSlider.setSliderStyle(juce::Slider::Rotary);
    haasColorSlider.setScrollWheelEnabled(false);
    haasColorSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    haasColorSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    haasColorLabel.setText("Haas Color", NotificationType::dontSendNotification);
    haasColorLabel.attachToComponent(&haasColorSlider, false);
    addAndMakeVisible(haasColorSlider);
    haasColorSliderAttachment.reset(new SliderAttachment(valueTreeState, "haasColor", haasColorSlider));

    haasBalanceSlider.setSliderStyle(juce::Slider::Rotary);
    haasBalanceSlider.setScrollWheelEnabled(false);
    haasBalanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    haasBalanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    haasBalanceLabel.setText("Haas Balance", NotificationType::dontSendNotification);
    haasBalanceLabel.attachToComponent(&haasBalanceSlider, false);
    addAndMakeVisible(haasBalanceSlider);
    haasBalanceSliderAttachment.reset(new SliderAttachment(valueTreeState, "haasBalance", haasBalanceSlider));

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
    
    auto sliderWidth = availableArea.getWidth() /3;
    auto sliderHeight = availableArea.getHeight() / 2;

    auto firstRow = availableArea.removeFromTop(sliderHeight);
    haasDelaySlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));
    haasColorSlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));
    haasBalanceSlider.setBounds(firstRow.removeFromLeft(sliderWidth).reduced(30));

    auto secondRow = availableArea.removeFromTop(sliderHeight);
    wideningDriveSlider.setBounds(secondRow.removeFromLeft(sliderWidth).reduced(30));
    wideningFactorSlider.setBounds(secondRow.removeFromLeft(sliderWidth).reduced(30));  
    wideningSpaceSlider.setBounds(secondRow.removeFromLeft(sliderWidth).reduced(30));  
}

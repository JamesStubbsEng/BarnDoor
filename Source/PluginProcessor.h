/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "dsp/Widen.h"
#include "dsp/Haas.h"

//==============================================================================
/**
*/
class BarnDoorAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    BarnDoorAudioProcessor();
    ~BarnDoorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool canGetLeftAndRightChannelSamples();
    void getLeftAndRightChannelSamples(float& l, float& r);

private:
    //==============================================================================
    AudioProcessorValueTreeState parameters;

    std::atomic<float>* wideningFactor = nullptr;
    std::atomic<float>* wideningDrive = nullptr;
    std::atomic<float>* haasDelayTime = nullptr;

    std::atomic<float> leftChannelSample{ 0.f };
    std::atomic<float> rightChannelSample{ 0.f };
    std::atomic<bool> isPlaying{ true };

    Widen widen;
    Haas haas;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarnDoorAudioProcessor)
};

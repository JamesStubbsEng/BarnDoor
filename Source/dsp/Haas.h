/*
  ==============================================================================

    Haas.h
    Created: 22 Sep 2023 10:41:35am
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Haas {
public:
    Haas() = default;
    void setDelayTime(float val);
    void prepare(float sampleRate, int32 maximumBlockSize, int32 numberOfChannels) noexcept;
    void processBlock(juce::AudioBuffer<float>& buffer) noexcept;
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> delayTimeSmoothedMs;
    juce::dsp::DelayLine<float> delayLine;
    float sampleRate = 44100.f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Haas)
};
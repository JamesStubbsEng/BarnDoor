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
    void setColorDriveDb(float val);
    void setBalanceDb(float val);
    void prepare(float sampleRate, int32 maximumBlockSize, int32 numberOfChannels, float delayTimeMs, float colorDriveDb, float balanceDb) noexcept;
    void processBlock(juce::AudioBuffer<float>& buffer) noexcept;
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> delayTimeSmoothedMs;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> colorDriveSmoothedDb;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> balanceSmoothedDb;
    juce::dsp::DelayLine<float> delayLine;
    float sampleRate = 44100.f;
    dsp::WaveShaper<float> shaper{ dsp::FastMathApproximations::tanh };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Haas)
};
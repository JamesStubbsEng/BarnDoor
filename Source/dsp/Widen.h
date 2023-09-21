/*
  ==============================================================================

    Widen.h
    Created: 21 Sep 2023 12:04:50pm
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Widen {
public:
    Widen() = default;
    void setWideningFactor(float val);
    void setWideningGain(float valDB);
    void prepare(float sampleRate) noexcept;
    void processBlock(juce::AudioBuffer<float>& buffer) noexcept;
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wideningFactorSmoothed;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wideningGainSmoothed;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Widen)
};
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
    void setWideningSpaceWet(float val);
    void prepare(float sampleRate, int32 maximumBlockSize, int32 numberOfChannels, float wideningFactor, float wideningGainDb, float wideningSpaceMix) noexcept;
    void processBlock(juce::AudioBuffer<float>& buffer) noexcept;
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wideningFactorSmoothed;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wideningGainSmoothed;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> spaceMixSmoothed;
    dsp::WaveShaper<float> shaper{ dsp::FastMathApproximations::tanh };
    dsp::Convolution convolutionReverb;
    const float CONV_GAIN_DB = 5.0f;
    juce::AudioBuffer<float> reverbBuffer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Widen)
};
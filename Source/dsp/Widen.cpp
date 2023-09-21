/*
  ==============================================================================

    Widen.cpp
    Created: 21 Sep 2023 12:04:50pm
    Author:  James

  ==============================================================================
*/

#include "Widen.h"

void Widen::setWideningFactor(float val)
{
    wideningFactorSmoothed.setTargetValue(val);
}

void Widen::setWideningGain(float valDB)
{
    wideningGainSmoothed.setTargetValue(valDB);
}

void Widen::prepare(float sampleRate) noexcept
{
    wideningFactorSmoothed.setCurrentAndTargetValue(1.0f);
    wideningFactorSmoothed.reset(sampleRate, 0.05);
    wideningGainSmoothed.setCurrentAndTargetValue(0.0f);
    wideningGainSmoothed.reset(sampleRate, 0.05);
}

void Widen::processBlock(juce::AudioBuffer<float>& buffer) noexcept
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    jassert(numChannels < 3 && numChannels > 0);

    if (numChannels == 1)
        return;

    if(numChannels == 2)
    {
        for (size_t i = 0; i < numSamples; ++i)
        {
            // encode to MS
            auto leftSample = buffer.getSample(0, i);
            auto rightSample = buffer.getSample(1, i);
            auto mid = 0.5f * (leftSample + rightSample);
            auto side = 0.5f * (leftSample - rightSample);

            // apply widening factor
            auto wideningFactor = wideningFactorSmoothed.getNextValue();
            mid = (2 - wideningFactor) * mid;
            side = wideningFactor * side;

            // decode back to LR and apply gain
            auto wideningGain = Decibels::decibelsToGain(wideningGainSmoothed.getNextValue());
            buffer.setSample(0, i, wideningGain * (mid + side));
            buffer.setSample(1, i, wideningGain * (mid - side));
        }
    }
}

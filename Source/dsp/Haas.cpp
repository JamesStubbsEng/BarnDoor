/*
  ==============================================================================

    Haas.cpp
    Created: 22 Sep 2023 10:41:35am
    Author:  James

  ==============================================================================
*/

#include "Haas.h"

void Haas::setDelayTime(float val)
{
    delayTimeSmoothedMs.setTargetValue(val);
}

void Haas::setColorDriveDb(float val)
{
    colorDriveSmoothedDb.setTargetValue(val);
}

void Haas::setBalanceDb(float val)
{
    balanceSmoothedDb.setTargetValue(val);
}

void Haas::prepare(float sampleRate, int32 maximumBlockSize, int32 numberOfChannels, float delayTimeMs, float colorDriveDb, float balanceDb) noexcept
{
    delayTimeSmoothedMs.setCurrentAndTargetValue(delayTimeMs);
    delayTimeSmoothedMs.reset(sampleRate, 0.05);

    colorDriveSmoothedDb.setCurrentAndTargetValue(colorDriveDb);
    colorDriveSmoothedDb.reset(sampleRate, 0.05);

    balanceSmoothedDb.setCurrentAndTargetValue(balanceDb);
    balanceSmoothedDb.reset(sampleRate, 0.05);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = maximumBlockSize;
    spec.numChannels = numberOfChannels;
    spec.sampleRate = sampleRate;
    this->sampleRate = sampleRate;
    //setDelayLine to be 100ms
    delayLine.setMaximumDelayInSamples(0.1f * sampleRate);
    delayLine.prepare(spec);

}

void Haas::processBlock(juce::AudioBuffer<float>& buffer) noexcept
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    jassert(numChannels < 3 && numChannels > 0);

    if (numChannels == 1)
        return;

    if (numChannels == 2)
    {
        //just process right channel
        for (size_t i = 0; i < numSamples; ++i)
        {
            auto smoothedDelayTimeSamples = 0.001f * delayTimeSmoothedMs.getNextValue() * sampleRate;
            auto smoothedColorDrive = Decibels::decibelsToGain(colorDriveSmoothedDb.getNextValue());
            auto smoothedBalanceGain = Decibels::decibelsToGain(balanceSmoothedDb.getNextValue());

            delayLine.pushSample(1, buffer.getSample(1, i));
            auto delayedSample = delayLine.popSample(1, smoothedDelayTimeSamples);

            //tanh waveshaping of right channel
            delayedSample = shaper.processSample(delayedSample * smoothedColorDrive) / smoothedColorDrive;

            delayedSample *= smoothedBalanceGain;

            buffer.setSample(1, i, delayedSample);
        }
    }
}

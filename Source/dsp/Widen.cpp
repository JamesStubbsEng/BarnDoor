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

void Widen::setWideningSpaceWet(float val)
{
    spaceMixSmoothed.setTargetValue(val);
}

void Widen::prepare(float sampleRate, int32 maximumBlockSize, int32 numberOfChannels, float wideningFactor, float wideningGainDb, float wideningSpaceMix) noexcept
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = maximumBlockSize;
    spec.numChannels = numberOfChannels;
    spec.sampleRate = sampleRate;

    wideningFactorSmoothed.setCurrentAndTargetValue(wideningFactor);
    wideningFactorSmoothed.reset(sampleRate, 0.05);
    wideningGainSmoothed.setCurrentAndTargetValue(wideningGainDb);
    wideningGainSmoothed.reset(sampleRate, 0.05);
    spaceMixSmoothed.setCurrentAndTargetValue(wideningSpaceMix);
    spaceMixSmoothed.reset(sampleRate, 0.05);

    //convolution length 50ms
    size_t convolutionLengthSamples = sampleRate * (0.05f);
    convolutionReverb.loadImpulseResponse(BinaryData::P042__Small_Ambience_wav, BinaryData::P042__Small_Ambience_wavSize, dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::no, convolutionLengthSamples, dsp::Convolution::Normalise::yes);
    convolutionReverb.prepare(spec);

    reverbBuffer.setSize(numberOfChannels, maximumBlockSize);
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
        reverbBuffer.makeCopyOf(buffer, true);
        dsp::AudioBlock<float> block(reverbBuffer);
        auto context = juce::dsp::ProcessContextReplacing<float>(block);
        convolutionReverb.process(context);

        for (size_t i = 0; i < numSamples; ++i)
        {
            // encode to MS
            auto wideningDrive = Decibels::decibelsToGain(wideningGainSmoothed.getNextValue());
            auto leftSample = buffer.getSample(0, i) * wideningDrive;
            auto rightSample = buffer.getSample(1, i) * wideningDrive;
            auto mid = 0.5f * (leftSample + rightSample);
            auto side = 0.5f * (leftSample - rightSample);

            //get side of reverb 
            auto leftReverbSample = reverbBuffer.getSample(0, i);
            auto rightReverbSample = reverbBuffer.getSample(1, i);
            auto sideReverb = 0.5f * (leftReverbSample - rightReverbSample);

            //tanh waveshaping of side channel
            side = shaper.processSample(side);

            // apply widening factor
            auto wideningFactor = wideningFactorSmoothed.getNextValue();
            mid = (2 - wideningFactor) * mid;

            side = wideningFactor * side;

            //add reverb back into side
            side += sideReverb * spaceMixSmoothed.getNextValue() * Decibels::decibelsToGain(CONV_GAIN_DB);

            // decode back to LR
            buffer.setSample(0, i, (mid + side) / wideningDrive);
            buffer.setSample(1, i, (mid - side) / wideningDrive);

            ////reverb length test
            //buffer.setSample(0, i, leftReverbSample);
            //buffer.setSample(1, i, rightReverbSample);
        }
    }
}

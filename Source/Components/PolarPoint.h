/*
  ==============================================================================

    PolarPoint.h
    Created: 18 Sep 2023 1:01:50pm
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PolarPoint  : public juce::Component
{
public:
    PolarPoint(int x, int y, int diameter);
    ~PolarPoint() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool decrementAlpha();

private:
    float alpha = 1.0f;
    const float step = 0.01f;
    const int x, y, diameter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolarPoint)
};

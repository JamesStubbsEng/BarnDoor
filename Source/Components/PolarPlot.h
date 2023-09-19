/*
  ==============================================================================

    PolarPlot.h
    Created: 18 Sep 2023 12:57:21pm
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PolarPoint.h"

//==============================================================================
/*
*/
class PolarPlot  : public juce::Component, private juce::Timer
{
public:
    PolarPlot();
    ~PolarPlot() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    OwnedArray<PolarPoint> polarPoints;
    const int POINT_DIAMETER = 6;
    int margin = 20;
    const float AXIS_THICKNESS = 2;
    Rectangle<int> plottingBounds;
    AffineTransform axisRotationTransform;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolarPlot)
};

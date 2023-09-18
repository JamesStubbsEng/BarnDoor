/*
  ==============================================================================

    PolarPlot.cpp
    Created: 18 Sep 2023 12:57:21pm
    Author:  James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PolarPlot.h"

//==============================================================================
PolarPlot::PolarPlot()
{
    startTimerHz(60);
}

PolarPlot::~PolarPlot()
{
}

void PolarPlot::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);   // clear the background

    g.setColour(Colours::darkgrey);

    //semi-circles
    const float innerArcRadius = getWidth() / 2 - MARGIN - AXIS_THICKNESS / 2;
    const float outerArcRadius = getWidth() / 2 - MARGIN + AXIS_THICKNESS / 2;
    Path semiCircle;
    semiCircle.addCentredArc(getWidth() / 2, getHeight() - MARGIN, outerArcRadius, outerArcRadius, 0, 1.5 * MathConstants<float>::pi, 2.5 * MathConstants<float>::pi, true);
    g.fillPath(semiCircle);

    Path innerSemiCircle;
    innerSemiCircle.addCentredArc(getWidth() / 2, getHeight() - MARGIN, innerArcRadius, innerArcRadius, 0, 1.5 * MathConstants<float>::pi, 2.5 * MathConstants<float>::pi, true);
    g.setColour(Colours::black);
    g.fillPath(innerSemiCircle);

    //paint axis
    g.setColour(Colours::darkgrey);
    //x-axis
    g.fillRoundedRectangle(0, getHeight() - MARGIN - AXIS_THICKNESS/2, getWidth(), AXIS_THICKNESS, AXIS_THICKNESS /2 );
    //y-axis
    g.fillRoundedRectangle(getWidth() / 2 - AXIS_THICKNESS / 2, 0, AXIS_THICKNESS, getHeight(), AXIS_THICKNESS / 2);
}

void PolarPlot::resized()
{

}

void PolarPlot::timerCallback()
{
    for (int i = polarPoints.size(); --i >= 0; )
        if (!polarPoints.getUnchecked(i)->decrementAlpha())
            polarPoints.remove(i);

    //point withing margin

    auto x = jmap(Random::getSystemRandom().nextFloat(), (float)MARGIN, (float)getWidth() - MARGIN);
    auto y = jmap(Random::getSystemRandom().nextFloat(), (float)MARGIN, (float)getHeight() - MARGIN);


    //test code: generate one more PolarPoint object
    addAndMakeVisible(polarPoints.add(new PolarPoint(
        x,
        y,
        POINT_DIAMETER)));
        
}

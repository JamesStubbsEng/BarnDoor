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
    //const float innerArcRadius = getWidth() / 2 - margin - AXIS_THICKNESS / 2;
    //const float outerArcRadius = getWidth() / 2 - margin + AXIS_THICKNESS / 2;
    //Path semiCircle;
    //semiCircle.addCentredArc(getWidth() / 2, getHeight() - margin, outerArcRadius, outerArcRadius, 0, 1.5 * MathConstants<float>::pi, 2.5 * MathConstants<float>::pi, true);
    //g.fillPath(semiCircle);

    //Path innerSemiCircle;
    //innerSemiCircle.addCentredArc(getWidth() / 2, getHeight() - margin, innerArcRadius, innerArcRadius, 0, 1.5 * MathConstants<float>::pi, 2.5 * MathConstants<float>::pi, true);
    //g.setColour(Colours::black);
    //g.fillPath(innerSemiCircle);

    //paint axis
    g.setColour(Colours::darkgrey);

    //x-axis
    Path p;
    p.addRoundedRectangle(0, getHeight()  /2 - AXIS_THICKNESS / 2, getWidth(), AXIS_THICKNESS, AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);

    //y-axis
    p.clear();
    p.addRoundedRectangle(getWidth() / 2 - AXIS_THICKNESS / 2, 0, AXIS_THICKNESS, getHeight(), AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);

    //axis limit notches

}

void PolarPlot::resized()
{
    //PolarPlot must be a square!
    jassert(getWidth() == getHeight());

    if (getWidth() != getHeight())
        setSize(getWidth(), getWidth());

    //make the margins the diamond within a square
    margin = (getWidth() * (2 - MathConstants<float>::sqrt2))/4;

    axisRotationTransform = AffineTransform::rotation(0.25 * MathConstants<float>::pi, getWidth() / 2, getHeight() / 2);
}

void PolarPlot::timerCallback()
{
    for (int i = polarPoints.size(); --i >= 0; )
        if (!polarPoints.getUnchecked(i)->decrementAlpha())
            polarPoints.remove(i);

    //point withing margin
    float x = jmap(Random::getSystemRandom().nextFloat(), (float)margin, (float)getWidth() - margin);
    float y = jmap(Random::getSystemRandom().nextFloat(), (float)margin, (float)getHeight() - margin);

    axisRotationTransform.transformPoint(x, y);

    //test code: generate one more PolarPoint object
    addAndMakeVisible(polarPoints.add(new PolarPoint(
        x,
        y,
        POINT_DIAMETER)));       
}

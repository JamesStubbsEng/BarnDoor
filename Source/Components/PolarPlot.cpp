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
PolarPlot::PolarPlot(BarnDoorAudioProcessor& audioProcessor) : audioProcessor(audioProcessor)
{
    startTimerHz(60);
}

PolarPlot::~PolarPlot()
{
}

void PolarPlot::paint (juce::Graphics& g)
{
    g.fillAll (Colours::black);   // clear the background

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
    p.clear();
    p.addRoundedRectangle(margin - AXIS_THICKNESS / 2, getHeight()/2 - NOTCH_LENGTH/2, AXIS_THICKNESS, NOTCH_LENGTH, AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);

    p.clear();
    p.addRoundedRectangle(getWidth() - margin - AXIS_THICKNESS / 2, getHeight() / 2 - NOTCH_LENGTH / 2, AXIS_THICKNESS, NOTCH_LENGTH, AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);

    p.clear();
    p.addRoundedRectangle(getWidth()/2 - NOTCH_LENGTH / 2 , margin - AXIS_THICKNESS / 2, NOTCH_LENGTH, AXIS_THICKNESS, AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);

    p.clear();
    p.addRoundedRectangle(getWidth() / 2 - NOTCH_LENGTH / 2, getHeight() - margin - AXIS_THICKNESS / 2, NOTCH_LENGTH, AXIS_THICKNESS, AXIS_THICKNESS / 2);
    p.applyTransform(axisRotationTransform);
    g.fillPath(p);
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

    ////test code: generate one more PolarPoint object
    ////point withing margin
    //float x = jmap(Random::getSystemRandom().nextFloat(), (float)margin, (float)getWidth() - margin);
    //float y = jmap(Random::getSystemRandom().nextFloat(), (float)margin, (float)getHeight() - margin);
    ////test code end

    //get left and right channel values and plot within margin

    //if the playhead is paused, don't draw anything new
    if (!audioProcessor.canGetLeftAndRightChannelSamples())
        return;

    float x = 0.f;
    float y = 0.f;
    audioProcessor.getLeftAndRightChannelSamples(x, y);
    x = jmap((x + 1.0f)/2, (float)margin, (float)getWidth() - margin);
    y = jmap((y + 1.0f) / 2, (float)margin, (float)getHeight() - margin);

    axisRotationTransform.transformPoint(x, y);

    addAndMakeVisible(polarPoints.add(new PolarPoint(
        x,
        y,
        POINT_DIAMETER)));
}

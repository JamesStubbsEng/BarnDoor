/*
  ==============================================================================

    PolarPoint.cpp
    Created: 18 Sep 2023 1:01:50pm
    Author:  James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PolarPoint.h"

//==============================================================================
PolarPoint::PolarPoint(int x, int y, int diameter) : x(x), y(y), diameter(diameter)
{
    setSize(diameter, diameter);
    setCentrePosition(x, y);
}

PolarPoint::~PolarPoint()
{
}

void PolarPoint::paint (juce::Graphics& g)
{
    g.setColour(Colours::aquamarine);
    g.setOpacity(alpha);
    g.fillEllipse(0, 0, getWidth(), getHeight());
}

void PolarPoint::resized()
{

}

bool PolarPoint::decrementAlpha()
{
    alpha = jlimit<float>(0,1, alpha - step);
    repaint();
    return alpha > 0.f;
}

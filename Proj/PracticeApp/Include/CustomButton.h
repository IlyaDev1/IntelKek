#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class CustomButton : public juce::Button
{
public:
    CustomButton(const juce::String& buttonName) : juce::Button(buttonName) {}

    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override
    {
        auto bounds = getLocalBounds().toFloat();

        g.setColour(isButtonDown ? juce::Colours::darkgrey : juce::Colours::lightgrey);
        g.fillRoundedRectangle(bounds, 6.0f);

        g.setColour(juce::Colours::black);
        g.setFont(juce::Font(16.0f));
        g.drawText(getButtonText(), bounds, juce::Justification::centred, true);
    }
};


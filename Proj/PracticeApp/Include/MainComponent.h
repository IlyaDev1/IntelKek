#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButton.h"

class MainComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    CustomButton playButton{ "Play" };
    CustomButton pauseButton{ "Pause" };
    CustomButton stopButton{ "Stop" };
    CustomButton nextButton{ "Next" };
    CustomButton prevButton{ "Previous" };
    CustomButton openButton{ "Open" };

    juce::Label currentFileLabel;
    juce::Slider positionSlider;

    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    AudioSourcePlayer sourcePlayer;

    AudioDeviceManager deviceManager;

    void openButtonClicked();
    void playNextTrack();
    void playPreviousTrack();
    void updateCurrentFileLabel();

    Array<File> audioFiles;
    int currentIndex = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

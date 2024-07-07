#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent : public Component,
    public Button::Listener,
    public FileDragAndDropTarget
{
public:
    MainComponent(void);
    ~MainComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;

    void buttonClicked(Button* button) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

private:
    TextButton playButton;
    TextButton pauseButton;
    TextButton stopButton;
    TextButton nextButton;
    TextButton prevButton;
    TextButton openButton;

    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    AudioSourcePlayer sourcePlayer;

    AudioDeviceManager deviceManager;

    void openButtonClicked();
    void playNextTrack();
    void playPreviousTrack();

    Array<File> audioFiles;
    int currentIndex = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

/**
 * @file MainComponent.h
 *
 * @brief �������� ��������� ���������� ��� ���������� ������������.
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButton.h"

 /**
  * @class MainComponent
  *
  * @brief �������� ��������� ����������, ���������� �� ����������� ���������� � ���������� ������������.
  */
class MainComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
    /**
     * @brief ����������� MainComponent.
     */
    MainComponent();

    /**
     * @brief ���������� MainComponent.
     */
    ~MainComponent() override;

    /**
     * @brief ���������������� ������� ��������� ����������.
     *
     * @param g ������ Graphics ��� ���������.
     */
    void paint(juce::Graphics& g) override;

    /**
     * @brief ���������������� ������� ��������� �������� ����������.
     */
    void resized() override;

    /**
     * @brief ���������� ������� ������� ������.
     *
     * @param button ��������� �� ������� ������.
     */
    void buttonClicked(juce::Button* button) override;

    /**
     * @brief ��������, ������������� �� ��������� � �������������� ������.
     *
     * @param files ������ ����� � ��������������� ������.
     * @return true, ���� ��������� ������������� � �������������� ������, ����� false.
     */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    /**
     * @brief ���������� ������� �������������� ������ � ���������.
     *
     * @param files ������ ����� � ��������������� ������.
     * @param x ���������� X �����, ��� ��������� �������.
     * @param y ���������� Y �����, ��� ��������� �������.
     */
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /**
     * @brief ���������� ��������� �������� ��������.
     *
     * @param slider ��������� �� �������, �������� �������� ����������.
     */
    void sliderValueChanged(juce::Slider* slider) override;

    /**
     * @brief Callback-������� �������, ���������� ������������.
     */
    void timerCallback() override;

private:
    CustomButton playButton{ "Play" };      /**< ������ ���������������. */
    CustomButton pauseButton{ "Pause" };    /**< ������ �����. */
    CustomButton stopButton{ "Stop" };      /**< ������ ���������. */
    CustomButton nextButton{ "Next" };      /**< ������ ���������� �����. */
    CustomButton prevButton{ "Previous" };  /**< ������ ����������� �����. */
    CustomButton openButton{ "Open" };      /**< ������ �������� �����. */

    juce::Label currentFileLabel;   /**< ����� ��� ����������� �������� �����. */
    juce::Slider positionSlider;    /**< ������� ��� ���������� �������� ���������������. */

    AudioFormatManager formatManager;               /**< �������� �������� �����������. */
    std::unique_ptr<AudioFormatReaderSource> readerSource; /**< �������� ������ ��� ��������������� �����. */
    AudioTransportSource transportSource;           /**< ������ ��� ���������� ���������������� �����. */
    AudioSourcePlayer sourcePlayer;                 /**< ����� �����������. */

    AudioDeviceManager deviceManager;   /**< �������� ��������������. */

    /**
     * @brief ���������� ������� ������ �������� �����.
     */
    void openButtonClicked();

    /**
     * @brief ��������������� ���������� �����.
     */
    void playNextTrack();

    /**
     * @brief ��������������� ����������� �����.
     */
    void playPreviousTrack();

    /**
     * @brief ���������� ����� �������� �����.
     */
    void updateCurrentFileLabel();

    Array<File> audioFiles;     /**< ������ ��������� �����������. */
    int currentIndex = -1;      /**< ������ �������� ���������� �����. */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

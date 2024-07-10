/**
 * @file MainComponent.h
 *
 * @brief Основной компонент приложения для управления аудиотреками.
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButton.h"

 /**
  * @class MainComponent
  *
  * @brief Основной компонент приложения, отвечающий за отображение интерфейса и управление аудиотреками.
  */
class MainComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
    /**
     * @brief Конструктор MainComponent.
     */
    MainComponent();

    /**
     * @brief Деструктор MainComponent.
     */
    ~MainComponent() override;

    /**
     * @brief Переопределенная функция отрисовки компонента.
     *
     * @param g Объект Graphics для рисования.
     */
    void paint(juce::Graphics& g) override;

    /**
     * @brief Переопределенная функция изменения размеров компонента.
     */
    void resized() override;

    /**
     * @brief Обработчик события нажатия кнопок.
     *
     * @param button Указатель на нажатую кнопку.
     */
    void buttonClicked(juce::Button* button) override;

    /**
     * @brief Проверка, заинтересован ли компонент в перетаскивании файлов.
     *
     * @param files Массив путей к перетаскиваемым файлам.
     * @return true, если компонент заинтересован в перетаскивании файлов, иначе false.
     */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    /**
     * @brief Обработчик события перетаскивания файлов в компонент.
     *
     * @param files Массив путей к перетаскиваемым файлам.
     * @param x Координата X точки, где произошло событие.
     * @param y Координата Y точки, где произошло событие.
     */
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /**
     * @brief Обработчик изменения значения слайдера.
     *
     * @param slider Указатель на слайдер, значение которого изменилось.
     */
    void sliderValueChanged(juce::Slider* slider) override;

    /**
     * @brief Callback-функция таймера, вызывается периодически.
     */
    void timerCallback() override;

private:
    CustomButton playButton{ "Play" };      /**< Кнопка воспроизведения. */
    CustomButton pauseButton{ "Pause" };    /**< Кнопка паузы. */
    CustomButton stopButton{ "Stop" };      /**< Кнопка остановки. */
    CustomButton nextButton{ "Next" };      /**< Кнопка следующего трека. */
    CustomButton prevButton{ "Previous" };  /**< Кнопка предыдущего трека. */
    CustomButton openButton{ "Open" };      /**< Кнопка открытия файла. */

    juce::Label currentFileLabel;   /**< Метка для отображения текущего файла. */
    juce::Slider positionSlider;    /**< Слайдер для управления позицией воспроизведения. */

    AudioFormatManager formatManager;               /**< Менеджер форматов аудиофайлов. */
    std::unique_ptr<AudioFormatReaderSource> readerSource; /**< Источник данных для воспроизведения аудио. */
    AudioTransportSource transportSource;           /**< Объект для управления воспроизведением аудио. */
    AudioSourcePlayer sourcePlayer;                 /**< Плеер аудиоданных. */

    AudioDeviceManager deviceManager;   /**< Менеджер аудиоустройств. */

    /**
     * @brief Обработчик нажатия кнопки открытия файла.
     */
    void openButtonClicked();

    /**
     * @brief Воспроизведение следующего трека.
     */
    void playNextTrack();

    /**
     * @brief Воспроизведение предыдущего трека.
     */
    void playPreviousTrack();

    /**
     * @brief Обновление метки текущего файла.
     */
    void updateCurrentFileLabel();

    Array<File> audioFiles;     /**< Массив выбранных аудиофайлов. */
    int currentIndex = -1;      /**< Индекс текущего выбранного трека. */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

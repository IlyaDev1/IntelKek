#include "../Include/MainComponent.h"

MainComponent::MainComponent(void)
{
    setOpaque(true);
    setSize(800, 800);

    // Инициализация кнопок
    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(pauseButton);
    pauseButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(nextButton);
    nextButton.addListener(this);

    addAndMakeVisible(prevButton);
    prevButton.addListener(this);

    addAndMakeVisible(openButton);
    openButton.addListener(this);

    // Инициализация метки
    addAndMakeVisible(currentFileLabel);
    currentFileLabel.setJustificationType(juce::Justification::centred);
    currentFileLabel.setFont(juce::Font(16.0f));
    currentFileLabel.setColour(Label::textColourId, Colours::black);  // Сделать текст черным

    // Инициализация слайдера
    addAndMakeVisible(positionSlider);
    positionSlider.setRange(0.0, 1.0);
    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    positionSlider.addListener(this);

    // Настройка аудио
    formatManager.registerBasicFormats();
    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&sourcePlayer);
    sourcePlayer.setSource(&transportSource);

    startTimer(100);  // Запуск таймера с интервалом 100 мс
}

MainComponent::~MainComponent(void)
{
    stopTimer();  // Остановка таймера
    sourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&sourcePlayer);
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colours::powderblue);
}

void MainComponent::resized(void)
{
    auto area = getLocalBounds();
    playButton.setBounds(area.removeFromTop(40).reduced(10));
    pauseButton.setBounds(area.removeFromTop(40).reduced(10));
    stopButton.setBounds(area.removeFromTop(40).reduced(10));
    nextButton.setBounds(area.removeFromTop(40).reduced(10));
    prevButton.setBounds(area.removeFromTop(40).reduced(10));
    openButton.setBounds(area.removeFromTop(40).reduced(10));
    currentFileLabel.setBounds(area.removeFromTop(40).reduced(10));
    positionSlider.setBounds(area.removeFromTop(40).reduced(10));
}

void MainComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        transportSource.start();
    }
    else if (button == &pauseButton)
    {
        transportSource.stop();
    }
    else if (button == &stopButton)
    {
        transportSource.stop();
        transportSource.setPosition(0.0);
    }
    else if (button == &nextButton)
    {
        playNextTrack();
    }
    else if (button == &prevButton)
    {
        playPreviousTrack();
    }
    else if (button == &openButton)
    {
        openButtonClicked();
    }
}

bool MainComponent::isInterestedInFileDrag(const StringArray& files)
{
    for (auto& file : files)
        if (formatManager.findFormatForFileExtension(File(file).getFileExtension()) != nullptr)
            return true;

    return false;
}

void MainComponent::filesDropped(const StringArray& files, int x, int y)
{
    for (auto& file : files)
    {
        auto* reader = formatManager.createReaderFor(File(file));

        if (reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());
            break;
        }
    }
    updateCurrentFileLabel();
}

void MainComponent::openButtonClicked()
{
    FileChooser chooser("Select audio files...",
        File::getSpecialLocation(File::userMusicDirectory),
        "*.wav;*.mp3;*.aiff");

    if (chooser.browseForMultipleFilesToOpen())
    {
        audioFiles.clear();
        Array<File> chosenFiles = chooser.getResults();
        for (const auto& file : chosenFiles)
        {
            audioFiles.add(file);
        }

        if (!audioFiles.isEmpty())
        {
            currentIndex = 0;
            auto* reader = formatManager.createReaderFor(audioFiles[currentIndex]);

            if (reader != nullptr)
            {
                std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
                transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
                readerSource.reset(newSource.release());
            }
        }
    }
    updateCurrentFileLabel();
}

void MainComponent::playNextTrack()
{
    if (!audioFiles.isEmpty() && currentIndex < audioFiles.size() - 1)
    {
        currentIndex++;
        auto* reader = formatManager.createReaderFor(audioFiles[currentIndex]);

        if (reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());
            transportSource.start();
        }
    }
    updateCurrentFileLabel();
}

void MainComponent::playPreviousTrack()
{
    if (!audioFiles.isEmpty() && currentIndex > 0)
    {
        currentIndex--;
        auto* reader = formatManager.createReaderFor(audioFiles[currentIndex]);

        if (reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());
            transportSource.start();
        }
    }
    updateCurrentFileLabel();
}

void MainComponent::updateCurrentFileLabel()
{
    if (currentIndex >= 0 && currentIndex < audioFiles.size())
    {
        currentFileLabel.setText(audioFiles[currentIndex].getFileNameWithoutExtension(), juce::dontSendNotification);
    }
    else
    {
        currentFileLabel.setText("", juce::dontSendNotification);
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &positionSlider)
    {
        if (transportSource.isPlaying())
        {
            transportSource.setPosition(transportSource.getLengthInSeconds() * positionSlider.getValue());
        }
    }
}

void MainComponent::timerCallback()
{
    if (transportSource.isPlaying())
    {
        double currentPosition = transportSource.getCurrentPosition();
        double trackLength = transportSource.getLengthInSeconds();
        if (trackLength > 0.0)
        {
            positionSlider.setValue(currentPosition / trackLength, dontSendNotification);
        }
    }
}

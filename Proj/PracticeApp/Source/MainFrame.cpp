#include "../JuceLibraryCode/JuceHeader.h"
#include "../Include/MainFrame.h"
#include "../Include/Application.h"

MainFrame::MainFrame(const String& name)
    : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setResizable(true, false);
    setResizeLimits(400, 400, 10000, 10000);

    setContentOwned(new MainComponent(), false);
    setVisible(true);
}

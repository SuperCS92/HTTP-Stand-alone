/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Channel.h"


//==============================================================================
MainComponent::MainComponent()
{

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (16, 16); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (16, 16);
    }
    
    addAndMakeVisible(ch1);
    addAndMakeVisible(ch2);
    addAndMakeVisible(ch3);
    addAndMakeVisible(ch4);
    addAndMakeVisible(ch5);
    addAndMakeVisible(ch6);
    addAndMakeVisible(ch7);
    addAndMakeVisible(ch8);
    addAndMakeVisible(ch9);
    addAndMakeVisible(ch10);
    addAndMakeVisible(ch11);
    addAndMakeVisible(ch12);
    addAndMakeVisible(ch13);
    addAndMakeVisible(ch14);
    addAndMakeVisible(ch15);
    addAndMakeVisible(ch16);
    
    
    addAndMakeVisible (urlBox);
    urlBox.onReturnKey = [this] {
        fetchButton.triggerClick();
        //DBG("Enter pressed");
    };
    urlBox.setTextToShowWhenEmpty("Introduce an URL & press Change URL", Colours::white);
    
    
    addAndMakeVisible (fetchButton);
    fetchButton.onClick = [this] {
        url = static_cast<URL>(urlBox.getText()) ;
                                };
    
    
     startTimer (1000);        //The values will be updated every second
        
    
    addAndMakeVisible(SendAllButton);
    SendAllButton.onClick = [this] (){ sendAll();};
    

     
    timerMenu.addItem("0.5 Seconds", 1);
    timerMenu.addItem("1 Second", 2);
    timerMenu.addItem("2 Seconds", 3);
    timerMenu.addItem("4 Seconds", 4);
    timerMenu.setJustificationType(Justification::centred);
    timerMenu.addListener(this);
    timerMenu.setSelectedItemIndex(1);
    addAndMakeVisible (timerMenu);
    
   
    
     
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (400, 350);
    
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels  = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    auto maxInputChannels  = activeInputChannels .getHighestBit() + 1;
    auto maxOutputChannels = activeOutputChannels.getHighestBit() + 1;
    
    
    for (auto channel = 0; channel < maxOutputChannels; ++channel)
    {
        if ((! activeOutputChannels[channel]) || maxInputChannels == 0)
        {
            bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
        }
        else
        {
            auto actualInputChannel = channel % maxInputChannels;
            
            if (! activeInputChannels[channel])
            {
                bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
            }
            else
            {
                
                auto* inBuffer = bufferToFill.buffer->getReadPointer (actualInputChannel,
                                                                      bufferToFill.startSample);
                auto* outBuffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
                
                for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                    outBuffer[sample] = inBuffer[sample];
                
                getRMSValuesForAllChannels(bufferToFill);
           }
        }
    }
    
    
  
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    
    {
        auto topArea = area.removeFromTop (40);
        fetchButton.setBounds (topArea.removeFromRight (100).reduced (8));
        urlBox     .setBounds (topArea.reduced (8));
    }
    
    
    auto firstRow = area.removeFromTop(70).removeFromRight(340);
    auto secondRow = area.removeFromTop(70).removeFromRight(340);
    auto thirdRow = area.removeFromTop(70).removeFromRight(340);
    auto fourthRow = area.removeFromTop(70).removeFromRight(340);
    auto timerArea = area.removeFromTop(70).removeFromRight(340);
    
    ch1.setBounds(firstRow.removeFromLeft(70).reduced(8));
    ch2.setBounds(firstRow.removeFromLeft(70).reduced(8));
    ch3.setBounds(firstRow.removeFromLeft(70).reduced(8));
    ch4.setBounds(firstRow.removeFromLeft(70).reduced(8));
    
    SendAllButton.setBounds(firstRow.removeFromLeft(90).reduced(5));
    
    ch5.setBounds(secondRow.removeFromLeft(70).reduced(8));
    ch6.setBounds(secondRow.removeFromLeft(70).reduced(8));
    ch7.setBounds(secondRow.removeFromLeft(70).reduced(8));
    ch8.setBounds(secondRow.removeFromLeft(70).reduced(8));
    
    ch9.setBounds(thirdRow.removeFromLeft(70).reduced(8));
    ch10.setBounds(thirdRow.removeFromLeft(70).reduced(8));
    ch11.setBounds(thirdRow.removeFromLeft(70).reduced(8));
    ch12.setBounds(thirdRow.removeFromLeft(70).reduced(8));
    
    ch13.setBounds(fourthRow.removeFromLeft(70).reduced(8));
    ch14.setBounds(fourthRow.removeFromLeft(70).reduced(8));
    ch15.setBounds(fourthRow.removeFromLeft(70).reduced(8));
    ch16.setBounds(fourthRow.removeFromLeft(70).reduced(8));
    
    timerMenu.setBounds(timerArea.removeFromLeft(280).reduced(5));
    
}

void MainComponent::getRMSValuesForAllChannels(const AudioSourceChannelInfo& bufferToFill)
{
    auto numChannels = bufferToFill.buffer->getNumChannels();
    if (numChannels > 1)
        ch1RMS = bufferToFill.buffer->getRMSLevel(0, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 2)
    ch2RMS = bufferToFill.buffer->getRMSLevel(1, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 3)
    ch3RMS = bufferToFill.buffer->getRMSLevel(2, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 4)
    ch4RMS = bufferToFill.buffer->getRMSLevel(3, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 5)
    ch5RMS = bufferToFill.buffer->getRMSLevel(4, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 6)
    ch6RMS = bufferToFill.buffer->getRMSLevel(5, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 7)
    ch7RMS = bufferToFill.buffer->getRMSLevel(6, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 8)
    ch8RMS = bufferToFill.buffer->getRMSLevel(7, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 9)
    ch9RMS = bufferToFill.buffer->getRMSLevel(8, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 10)
    ch10RMS = bufferToFill.buffer->getRMSLevel(9, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 11)
    ch11RMS = bufferToFill.buffer->getRMSLevel(10, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 12)
    ch12RMS = bufferToFill.buffer->getRMSLevel(11, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 13)
    ch13RMS = bufferToFill.buffer->getRMSLevel(12, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 14)
    ch14RMS = bufferToFill.buffer->getRMSLevel(13, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 15)
    ch15RMS = bufferToFill.buffer->getRMSLevel(14, 0, bufferToFill.buffer->getNumSamples());
    
    if (numChannels > 16)
    ch16RMS = bufferToFill.buffer->getRMSLevel(15, 0, bufferToFill.buffer->getNumSamples());
    
}

String MainComponent::valueToString(float value)
{
    auto levelInDecibels = Decibels::gainToDecibels(value);
    String level (Decibels::toString(levelInDecibels,1));
    
    return level;
}


void MainComponent::valueToStringForAllChannels(String& Sch1, String& Sch2, String& Sch3, String& Sch4,
                                                              String& Sch5, String& Sch6, String& Sch7, String& Sch8,
                                                              String& Sch9, String& Sch10, String& Sch11, String& Sch12,
                                                              String& Sch13, String& Sch14, String& Sch15, String& Sch16)
{
    Sch1 = valueToString(ch1RMS);
    Sch2 = valueToString(ch2RMS);
    Sch3 = valueToString(ch3RMS);
    Sch4 = valueToString(ch4RMS);
    Sch5 = valueToString(ch5RMS);
    Sch6 = valueToString(ch6RMS);
    Sch7 = valueToString(ch7RMS);
    Sch8 = valueToString(ch8RMS);
    Sch9 = valueToString(ch9RMS);
    Sch10 = valueToString(ch10RMS);
    Sch11 = valueToString(ch11RMS);
    Sch12 = valueToString(ch12RMS);
    Sch13 = valueToString(ch13RMS);
    Sch14 = valueToString(ch14RMS);
    Sch15 = valueToString(ch15RMS);
    Sch16 = valueToString(ch16RMS);
    
}

void MainComponent::updateLevelsForAllChannels(String& Sch1, String& Sch2, String& Sch3, String& Sch4,
                                                             String& Sch5, String& Sch6, String& Sch7, String& Sch8,
                                                             String& Sch9, String& Sch10, String& Sch11, String& Sch12,
                                                             String& Sch13, String& Sch14, String& Sch15, String& Sch16)
{
    ch1.updateLevel(Sch1);
    ch2.updateLevel(Sch2);
    ch3.updateLevel(Sch3);
    ch4.updateLevel(Sch4);
    ch5.updateLevel(Sch5);
    ch6.updateLevel(Sch6);
    ch7.updateLevel(Sch7);
    ch8.updateLevel(Sch8);
    ch9.updateLevel(Sch9);
    ch10.updateLevel(Sch10);
    ch11.updateLevel(Sch11);
    ch12.updateLevel(Sch12);
    ch13.updateLevel(Sch13);
    ch14.updateLevel(Sch14);
    ch15.updateLevel(Sch15);
    ch16.updateLevel(Sch16);
}

String MainComponent::jsonMessage()
{
    DynamicObject* obj = new DynamicObject();
    obj->setProperty("Message Empty", "All Channels Disabled");
    
    if ( ch1.getButtonState()==true) {
        obj->setProperty("Ch1",Decibels::gainToDecibels(ch1RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch2.getButtonState() == true) {
        obj->setProperty("Ch2",Decibels::gainToDecibels(ch2RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch3.getButtonState() == true) {
        obj->setProperty("Ch3",Decibels::gainToDecibels(ch3RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch4.getButtonState() ==true) {
        obj->setProperty("Ch4",Decibels::gainToDecibels(ch4RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch5.getButtonState() == true) {
        obj->setProperty("Ch5",Decibels::gainToDecibels(ch5RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch6.getButtonState() == true) {
        obj->setProperty("Ch6",Decibels::gainToDecibels(ch6RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch7.getButtonState() == true) {
        obj->setProperty("Ch7",Decibels::gainToDecibels(ch7RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch8.getButtonState() == true) {
        obj->setProperty("Ch8",Decibels::gainToDecibels(ch8RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch9.getButtonState() == true) {
        obj->setProperty("Ch9",Decibels::gainToDecibels(ch9RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch10.getButtonState() ==true) {
        obj->setProperty("Ch10",Decibels::gainToDecibels(ch10RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch11.getButtonState() == true) {
        obj->setProperty("Ch11",Decibels::gainToDecibels(ch11RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch12.getButtonState() == true) {
        obj->setProperty("Ch12",Decibels::gainToDecibels(ch12RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch13.getButtonState() ==true) {
        obj->setProperty("Ch13",Decibels::gainToDecibels(ch13RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch14.getButtonState() == true) {
        obj->setProperty("Ch14",Decibels::gainToDecibels(ch14RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch15.getButtonState() == true) {
        obj->setProperty("Ch15",Decibels::gainToDecibels(ch15RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    if (ch16.getButtonState() == true) {
        obj->setProperty("Ch16",Decibels::gainToDecibels(ch16RMS));
        if (obj->hasProperty("Message Empty")) {
            obj->removeProperty("Message Empty");
        }
    }
    
    var json (obj);
    
    return JSON::toString(json);
    
}

void MainComponent::POST()
{
    if (!url.isEmpty())
    {
        StringPairArray responseHeaders;
        int statusCode = 0;
        
        //DBG ( "POST Method");
        
        String s = jsonMessage();
        
        if(!s.isEmpty())
        {
            url = url.withPOSTData(s);
            //DBG("Post data sended:");
            //DBG(s);
        }
        
        std::unique_ptr<InputStream> stream (url.createInputStream (true, nullptr, nullptr, {"Content-Type: application/json"}, 10000, &responseHeaders, &statusCode, 5, "POST"));
        
        String response  = stream->readEntireStreamAsString().toStdString();
        String head = responseHeaders.getDescription().toStdString();
        if (stream.get() != nullptr)
        {
            std::cout<<"status code: "<<statusCode<<std::endl;
            std::cout<<head<<std::endl;
            std::cout<<response<<std::endl;
            //DBG("Stream is not empty");
        }
        
    }
    
}

void MainComponent::timerCallback()
{
    valueToStringForAllChannels(levelCh1, levelCh2, levelCh3, levelCh4,
                                levelCh5, levelCh6, levelCh7, levelCh8,
                                levelCh9, levelCh10, levelCh11, levelCh12,
                                levelCh13, levelCh14, levelCh15, levelCh16);
    
    updateLevelsForAllChannels (levelCh1, levelCh2, levelCh3, levelCh4,
                                levelCh5, levelCh6, levelCh7, levelCh8,
                                levelCh9, levelCh10, levelCh11, levelCh12,
                                levelCh13, levelCh14, levelCh15, levelCh16);
    
      POST();
}

void MainComponent::comboBoxChanged(ComboBox* box)
{
    
    if (box == &timerMenu)
    {
        if (timerMenu.getSelectedId() == 1)
        {
            startTimer(500);
            //DBG("500ms");
        }
        else if (timerMenu.getSelectedId() == 2)
        {
            startTimer(1000);
            //DBG("1Second");
        }
        else if (timerMenu.getSelectedId() == 3)
        {
            startTimer(2000);
            //DBG("2Second");
        }
        else if (timerMenu.getSelectedId() == 4)
        {
            startTimer(4000);
            // DBG("4Second");
        }
        
    }
}

void MainComponent::sendAll()
{
    
    ch1.LedTriggerClick();
    ch2.LedTriggerClick();
    ch3.LedTriggerClick();
    ch4.LedTriggerClick();
    ch5.LedTriggerClick();
    ch6.LedTriggerClick();
    ch7.LedTriggerClick();
    ch8.LedTriggerClick();
    ch9.LedTriggerClick();
    ch10.LedTriggerClick();
    ch11.LedTriggerClick();
    ch12.LedTriggerClick();
    ch13.LedTriggerClick();
    ch14.LedTriggerClick();
    ch15.LedTriggerClick();
    ch16.LedTriggerClick();
}



/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Channel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Timer,
                        private ComboBox::Listener

{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    //===============================================================================
    /* This methods return the current RMS value from ALL channel */
    void getRMSValuesForAllChannels(const AudioSourceChannelInfo& bufferToFill);
    
    //==============================================================================
    /* Receives the current RMS value of a given channel, turns it to decibels and then String */
    String valueToString(float);
    
    //==============================================================================
    /* Call valueToString() for all channels */
    void valueToStringForAllChannels(String&, String&, String&, String&, String&, String&, String&, String&, String&, String&, String&, String&,String&, String&, String&, String&);
    
    //==============================================================================
    /* Call updateLevel() for all channels */
    void updateLevelsForAllChannels(String&, String&, String&, String&, String&, String&, String&, String&, String&, String&, String&, String&,String&, String&, String&, String&);
    
    //===============================================================================
    /* This methods return the JSON message will all the values that should be send in the POST request */
    String jsonMessage();
    
    //===============================================================================
    /* Sends a POST request */
    void POST();
    
    //==============================================================================
    /* Change the state of ALL Led_ TextButton from true to false or viceversa,
     this method is called when the SendAllButton is clicked */
    void sendAll();
    
   void timerCallback() override;
    
    //==============================================================================
    /* Restart the timer and set the new interval between POST request and the updates of the values */
    void comboBoxChanged(ComboBox*) override;
    

private:
   
    
    //==============================================================================
    /* Instantiation of 16 channels */
    Channel ch1 {"Ch1"};
    Channel ch2 {"Ch2"};
    Channel ch3 {"Ch3"};
    Channel ch4 {"Ch4"};
    Channel ch5 {"Ch5"};
    Channel ch6 {"Ch6"};
    Channel ch7 {"Ch7"};
    Channel ch8 {"Ch8"};
    Channel ch9 {"Ch9"};
    Channel ch10 {"Ch10"};
    Channel ch11 {"Ch11"};
    Channel ch12 {"Ch12"};
    Channel ch13 {"Ch13"};
    Channel ch14 {"Ch14"};
    Channel ch15 {"Ch15"};
    Channel ch16 {"Ch16"};
    
    //===============================================================================
    /* Holds the value of each channel */
    float ch1RMS{0.0f};
    float ch2RMS{0.0f};
    float ch3RMS{0.0f};
    float ch4RMS{0.0f};
    float ch5RMS{0.0f};
    float ch6RMS{0.0f};
    float ch7RMS{0.0f};
    float ch8RMS{0.0f};
    float ch9RMS{0.0f};
    float ch10RMS{0.0f};
    float ch11RMS{0.0f};
    float ch12RMS{0.0f};
    float ch13RMS{0.0f};
    float ch14RMS{0.0f};
    float ch15RMS{0.0f};
    float ch16RMS{0.0f};
    
    //==============================================================================
    /* Each String holds the current value of each channel */
    String levelCh1, levelCh2, levelCh3, levelCh4,
    levelCh5, levelCh6, levelCh7, levelCh8,
    levelCh9, levelCh10, levelCh11, levelCh12,
    levelCh13, levelCh14, levelCh15, levelCh16;
    
    //===============================================================================
    URL url; 
    TextEditor urlBox;                          // Here will be the url where the POST request will be sended
    TextButton fetchButton { "Change URL " };
    
    TextButton SendAllButton { "Send All" };
    
    
    ComboBox timerMenu;               //This comboBox will allow the user to set the interval between every POST request,
                                     // 0.5 seconds, 1 second, 2 seconds, 4 seconds
    
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

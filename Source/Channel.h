/*
  ==============================================================================

    Channel.h
    Created: 7 Jul 2020 8:18:43pm
    Author:  Carlos Segovia

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Channel    : public Component,
                   public Button::Listener
{
public:
    Channel();
    Channel(String labelNameText, String levelDisplayName = "LevelDisplay", String levelDisplayValue = "0.0", String LedName = " ", String LedToolTip = "Click to send this channel information");
    ~Channel();

    void paint (Graphics&) override;
    void resized() override;
    
    void updateLevel(String);       //updates the level display in levelDisplay Label
    bool getButtonState();          //returns the state of the Led_ TextButton
    void buttonClicked(Button *) override;  //change the state of the Led_ TextButton when clicked
    void LedTriggerClick();         //works as if the Led_ TextButton has been clicked, see SendAll() in PluginEditor

private:
    
    Label label_;           //Holds the name of the channel
    Label levelDisplay_;    //Display the current RMS value of the channel
    TextButton Led_;        //Enable the current RMS value to be send as part of the message in the post request
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channel)
};

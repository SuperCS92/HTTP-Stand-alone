/*
  ==============================================================================

    Channel.cpp
    Created: 7 Jul 2020 8:18:43pm
    Author:  Carlos Segovia

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Channel.h"

//==============================================================================
Channel::Channel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

//==============================================================================
Channel::Channel(String labelNameText, String levelDisplayName, String levelDisplayValue, String LedName,String LedToolTip):
label_(labelNameText,labelNameText),
levelDisplay_(levelDisplayName,levelDisplayValue),
Led_(LedName,LedToolTip)
{
    setSize(50, 50);
    
    label_.setEditable(false);
    addAndMakeVisible(&label_);
    
    levelDisplay_.setEditable(false);
    
    addAndMakeVisible(&levelDisplay_);
    
    
    addAndMakeVisible(Led_);
    Led_.setToggleState(false, NotificationType::dontSendNotification);
    Led_.onClick = [this](){};
    Led_.addListener(this);
    Led_.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    Led_.setColour(TextButton::ColourIds::buttonOnColourId, Colours::green);
    
}

Channel::~Channel()
{
}

void Channel::paint (Graphics& g)
{
     g.fillAll(Colours::grey);
}

void Channel::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    label_.setBounds(area.removeFromBottom(20));
    levelDisplay_.setBounds(area.removeFromBottom(20));
    Led_.setBounds(area.removeFromLeft(10));

}

void Channel::updateLevel(String value)
{
    levelDisplay_.setText(value, NotificationType::dontSendNotification);
    
}


bool Channel::getButtonState()
{
    return Led_.getToggleState();
}

void Channel::buttonClicked(Button * button)
{
    
    if (button == &Led_)
    {
        
        if (Led_.getToggleState() == true)
        {
            Led_.onClick = [this](){
                Led_.setToggleState(false, NotificationType::dontSendNotification);
                
            };
        }
        else
        {
            Led_.onClick = [this](){
                Led_.setToggleState(true, NotificationType::dontSendNotification);
                
            };
        }
    }
    
}

void Channel::LedTriggerClick()
{
    Led_.triggerClick();
}

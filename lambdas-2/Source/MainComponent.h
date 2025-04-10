#pragma once

#include <JuceHeader.h>

using namespace juce;

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void createRoot ();
    void mouseDown (const MouseEvent& e) override;
    
private:
	std::unique_ptr<Component> root;

	void highlightComponentsWithId (const String& colour);
	
    //==============================================================================
    // Your private member variables go here...



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

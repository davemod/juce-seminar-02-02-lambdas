#pragma once

#include <JuceHeader.h>

using namespace juce;

/**
 * This example shows some examples of lambdas and how you can use them. 
 * Look for @TODO in MainComponent.cpp.
 * 
 * When finished this is a simple game where you can left click to create
 * rectangles filled with a random colour and alt + click to highlight
 * all rectangles with the same colour as the one you clicked on.
 * 
 * The ColourComponent class is a recursive component that creates
 * children with a random colour and a random number of children.
 * 
 * A root is created and stored in a unique_ptr.
 */
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

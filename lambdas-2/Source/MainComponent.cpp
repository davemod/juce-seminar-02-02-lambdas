#include "MainComponent.h"

class ColourComponent : public Component, Timer
{
public:
    
    static inline StringArray AvailableColours {
        "red", "green", "blue", "yellow", "cyan", "magenta", "white", "grey", "orange", "purple", "pink"
    };

	ColourComponent (int hierarchy)
	{
        // @TODO: create a lambda that picks a random colour name from the array above.
        // to get a random number use juce::Random::getSystemRandom ().nextInt ()
        String colourString = [&](){};
        
        // component id will be our colour string
        setComponentID (colourString);
        
        // get an actual Colour object from our colour string to paint. create a darker and brighter colour
        colour = Colours::findColourForName(colourString, Colours::black);
		darkColour = colour.darker (1.f).darker (1.f);
		brightColour = colour;

        // create a random number of children
		if (hierarchy > 0)
			for (int i = Random::getSystemRandom ().nextInt (5) + 1; --i >= 0;)
				addAndMakeVisible (children.add (new ColourComponent (hierarchy - 1)));
	}

	void paint (Graphics& g) override
	{
		// @TODO: create a lambda called getColour which returns a darker colour if factor is negative 
		// and a brighter colour if factor is positive or colour if factor equals 0.
		// @see juce::Colour::interpolatedWith (otherColour, factor)

		g.fillAll (getColour ());
	}

	void resized () override
	{
		if (children.size() == 0)
			return;
		
		auto bounds = getLocalBounds ().reduced (2);
        if (bounds.isEmpty ()) return;
        
		auto size = (int)floor(jmin (bounds.getWidth (), bounds.getHeight ()) / (float)children.size ());
        
		// @TODO: create a lambda called getRandomCentre which returns a random point inside the bounds of the component.
		// @see juce::Random::getSystemRandom ().nextInt (int range)
		
		for (auto* child : children)
            child->setBounds (Rectangle (size, size).withCentre (getRandomCentre ()));
	}
    
    void mouseDown (const MouseEvent& e) override
    {
        if (auto parent = getParentComponent ())
            parent->mouseDown (e.getEventRelativeTo(parent));
    }

	void darken ()
	{
        set (-1.f);
	}

	void highlight ()
	{
        set (1.f);
	}

	void timerCallback () override
	{
		const auto next = [&](){
            if (inc < 0.f)
                return jmax (0.f, factor + inc);
            
            return jmin (0.f, factor + inc);
		};

        factor = next ();
        repaint ();
        
        if (factor == 0.f)
            stopTimer ();
	}

private:
   Colour colour, darkColour, brightColour;
                   
	float factor{ 0.f };
	float inc;

	void set (float x)
	{
		auto fps = 24.f;
		auto time = 5.f;

		factor = x;
		inc = -factor / (fps * time);
		startTimerHz (fps);
	}

    OwnedArray<Component> children;
};






//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 800);
}

MainComponent::~MainComponent()
{
}

void MainComponent::createRoot ()
{
    root = std::make_unique<ColourComponent> (4);
    addAndMakeVisible (root.get ());
    resized ();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Click to create colours!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    if (root)
        root->setBounds (getLocalBounds ());
}

void MainComponent::mouseDown (const MouseEvent& e)
{
    if (e.mods.isAltDown ())
    {
		if (auto o = e.originalComponent)
        	highlightComponentsWithId (o->getComponentID ());
    }
    else
    {
        createRoot ();
    }
}

void MainComponent::highlightComponentsWithId(const String &colour)
{
	auto highlight = [&] (Component * c){
		if (auto casted = dynamic_cast<ColourComponent*> (c))
			casted->highlight ();
	};

	auto darken = [&] (Component * c){
		if (auto casted = dynamic_cast<ColourComponent*> (c))
			casted->darken ();
	};

	/*  @TODO: create a std::function<void(Component*)> called recurseComponents which takes a Component pointer
		and recursively calls itself on all children of the component.

		if (component->getComponentID () == colour) it should call highlight, else darken.
	*/

	recurseComponents (root.get ());
}

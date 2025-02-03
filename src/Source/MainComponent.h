#pragma once

#include <JuceHeader.h>

#include "GSiAnimation8.h"      // Smoke

class MainComponent  : public juce::Component
{
public:
    static constexpr int FrameRate = 30;

    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    std::unique_ptr<GSiAnimatedAboutScreen> AnimationComponent;

    VBlankAttachment vba;
    double lastVBlankTime = 0.0;
	static constexpr double minTimeBetweenFramesMs = (1000.0 / (double)FrameRate) - 1.0;
    double FPS = 0.0;

    void Update()
    {
        //////////////////////////////////////////////////////
        auto now = juce::Time::getMillisecondCounterHiRes();
        auto elapsed = now - lastVBlankTime;
		if (elapsed < minTimeBetweenFramesMs) return;
        lastVBlankTime = now;
        ////////////////////////////////////////////////////////

		FPS = 1000.0 / elapsed;

        if (AnimationComponent)
            AnimationComponent->Update();
    }

	void paintOverChildren(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.drawText("FPS: " + String(FPS, 2), 0, 0, getWidth(), 20, juce::Justification::topRight);
	}


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

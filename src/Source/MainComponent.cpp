#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : vba(this, [&] { Update(); })
{
    setSize (1024, 512);
    AnimationComponent.reset(new GSiAnimatedAboutScreen());
    AnimationComponent->setBounds(0, 0, getWidth(), getHeight());
    addAndMakeVisible(AnimationComponent.get());
    AnimationComponent->Show();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::resized()
{
    if (AnimationComponent)
        AnimationComponent->setBounds(0, 0, getWidth(), getHeight());
}

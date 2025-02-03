
#pragma once

#include <JuceHeader.h> 

class GSiAnimatedAboutScreen : public Component
{
public:
	static constexpr int max_num_particles = 100;

    GSiAnimatedAboutScreen()
    {
        setOpaque(true);
        //setBufferedToImage(true);
    }

    void Show()
    {
        Update();
        toFront(true);
        setVisible(true);
    }

    void Hide()
    {
        Desktop::getInstance().getAnimator().fadeOut(this, 250);
    }

    void Update()
    {
        for (auto& particle : particles)
        {
            particle.x += particle.dx;
            particle.y += particle.dy;
			particle.size += particle.dsize;

            if (particle.y < -particle.size)
            {
                particle.reset(getWidth(), getHeight());
            }
        }

        repaint();
    }

private:
    Image PreviousFrame;

	void resized() override
	{
		PreviousFrame = Image(Image::PixelFormat::RGB, getWidth(), getHeight(), true);

		particles.clear();
		for (int i = 0; i < max_num_particles; ++i)
		{
			SmokeParticle newParticle;
			newParticle.reset(getWidth(), getHeight());
			particles.add(newParticle);
		}
	}

    struct SmokeParticle
    {
        float x, y;
        float dx, dy;
		float size, dsize;

        void reset(int width, int height)
        {
            juce::Random rnd;
            x = rnd.nextFloat() * width;
            y = height;
            dx = (rnd.nextFloat() - 0.5f) * 2.0f;
            dy = -1.0f - rnd.nextFloat() * 3.0f;
			size = 30.f + rnd.nextFloat() * 10.f;
			dsize = 0.1f + rnd.nextFloat() * 0.1f;
        }
    };

    juce::Array<SmokeParticle> particles;

    void paint(Graphics& g2) override
    {
        auto BMP = PreviousFrame.createCopy();
        Graphics g(BMP);

        g.fillAll(Colours::black);

        g.setOpacity(0.995f);
        g.drawImageAt(PreviousFrame, 0, 0);

        for (const auto& particle : particles)
        {
			auto rect = Rectangle<float>(particle.x, particle.y, particle.size, particle.size);
            DropShadow(Colour(0xA0808080), particle.size, Point<int>(0, 0)).drawForRectangle(g, rect.toNearestInt());

            //Path p;
			//p.addEllipse(particle.x, particle.y, particle.size, particle.size);
			//DropShadow(Colours::grey, 35, Point<int>(0, 0)).drawForPath(g, p);
        }

        // print the new frame and swap the two images
        //g2.drawImage(BMP, 0, 0, getWidth(), getHeight(), 0, 0, BMP.getWidth(), BMP.getHeight());
        g2.drawImageAt(BMP, 0, 0);
        PreviousFrame = BMP;

        //ImageConvolutionKernel blurKernel(3);
        //blurKernel.createGaussianBlur(3.0f);
        //blurKernel.applyToImage(PreviousFrame, BMP, BMP.getBounds());
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GSiAnimatedAboutScreen)
};

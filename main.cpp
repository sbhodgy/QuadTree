#include "AssetManager.hpp"
#include "QuadTree.hpp"
#include "Particle.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

int main()
{
    // general parameters for the scenario

    int width = 700;
    int height = 700;
    int maxVelocity = 200;
    int particleSize = 5.f;
    int numParticles = 10;

    std::vector<Particle> mParticles;

    // used to ensure a constant deltaTime

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // these are used to measure performance

    sf::Time updateTime;
    std::size_t numFrames;

    sf::Font font;
    sf::Text updateText;

    font.loadFromFile("../sansation.ttf");
    updateText.setFont(font);
    updateText.setPosition(5.f, 5.f);
    updateText.setCharacterSize(10u);
    updateText.setFillColor(sf::Color::White);

    // set up render window

    sf::RenderWindow window(sf::VideoMode(width, height), "Quad Tree Example");

    // create particles and add to the particle manager

    AssetManager particleMgr;

    std::srand(std::time(nullptr));

    for (int i = 0; i < numParticles; ++i)
    {
        // generate random position

        float xPosition = rand() % (width - particleSize);
        float yPosition = rand() % (height - particleSize);

        // generate random velocity

        float xVelocity = rand() % maxVelocity;
        float yVelocity = rand() % maxVelocity;

        // create the particle and add to the quad tree

        std::shared_ptr<Particle> particle(new Particle(sf::Vector2f(xPosition, yPosition), particleSize));

        particle->setVelocity(xVelocity, yVelocity);

        // particleMgr.addParticle(particle);

        mParticles.push_back(*particle);
    }

    sf::Clock clock;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            // particleMgr.update(TimePerFrame);
        }

        // measure performance

        updateTime += deltaTime;
        numFrames += 1;

        if (updateTime >= sf::seconds(1.0f))
        {
            updateText.setString("FPS: " + std::to_string(numFrames) + "\n" +
                                 std::to_string(updateTime.asMicroseconds() / numFrames));

            updateTime -= sf::seconds(1.0f);
            numFrames = 0;
        }

        // render particles and quad tree boundaries

        window.clear(sf::Color::Black);

        for (auto itr : mParticles)
        {
            itr.draw(window);
        }
        // particleMgr.draw(window);
        window.draw(updateText);
        window.display();
    }

    return 0;
}
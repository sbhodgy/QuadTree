#include "AssetManager.hpp"
// #include "QuadTree.hpp"

#include "Entity.hpp"
#include "Asset.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cassert>

int main()
{
    // general parameters for the scenario

    int width = 700;
    int height = 700;
    int maxVelocity = 200;
    int assetSize = 5.f;
    int numEntities = 350;

    // used to ensure a constant deltaTime

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // these are used to measure performance

    sf::Time updateTime;
    std::size_t numFrames;
    std::size_t numUpdates;

    sf::Font font;
    sf::Text updateText;

    font.loadFromFile("../sansation.ttf");
    updateText.setFont(font);
    updateText.setPosition(5.f, 5.f);
    updateText.setCharacterSize(15u);
    updateText.setFillColor(sf::Color::White);

    // set up render window

    sf::RenderWindow window(sf::VideoMode(width, height), "Quad Tree Example");

    // create particles and add to the particle manager

    AssetManager assetManager;

    std::srand(std::time(nullptr));

    for (int i = 0; i < numEntities; ++i)
    {
        // generate random position

        float xPosition = rand() % (width - assetSize);
        float yPosition = rand() % (height - assetSize);

        // generate random velocity

        float xVelocity = rand() % maxVelocity;
        float yVelocity = rand() % maxVelocity;

        // create the particle and add to the quad tree

        std::shared_ptr<Asset> particle(new Entity(sf::Vector2f(xPosition, yPosition), assetSize));

        if (i < numEntities)// / 4)
        {
            dynamic_cast<Entity&>(*particle).setVelocity(xVelocity, yVelocity);
        }
            

        assetManager.addEntity(particle);

        // mParticles.push_back(*particle);
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

            assetManager.update(TimePerFrame);

            numUpdates += 1;
        }

        // measure performance

        updateTime += deltaTime;
        numFrames += 1;

        if (updateTime >= sf::seconds(1.0f))
        {
            updateText.setString("Frames / Second: " + std::to_string(numFrames) + "\n" +
                                 "Time / Frame: " + std::to_string(updateTime.asSeconds() / numFrames) + "\n" +
                                 "Updates / Second: " + std::to_string(numUpdates));

            updateTime -= sf::seconds(1.0f);
            numFrames = 0;
            numUpdates = 0;
        }

        // render particles and quad tree boundaries

        window.clear(sf::Color::Black);
        assetManager.draw(window);
        window.draw(updateText);
        window.display();
    }

    return 0;
}
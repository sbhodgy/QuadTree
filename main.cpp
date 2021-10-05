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
    int numParticles = 250;

    // used to ensure a constant deltaTime

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // these are used to measure performance

    sf::Font font;
    sf::Text updateText;
    // sf::Time updateTime;
    // std::size_t frames = 0;

    font.loadFromFile("../sansation.ttf");
    updateText.setFont(font);
    updateText.setPosition(5.f, 5.f);
    updateText.setCharacterSize(10u);
    updateText.setFillColor(sf::Color::White);

    // set up render window

    sf::RenderWindow window(sf::VideoMode(width, height), "Quad Tree Example");

    sf::Vector2f position = sf::Vector2f(0.f, 0.f);
    sf::Vector2f size = sf::Vector2f(width, height);

    std::vector<std::shared_ptr<Particle>> particleSet;

    sf::Clock clock;

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

        particleSet.push_back(particle);
    }

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;

        QuadTree qTree(position, size);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            for (auto itr = particleSet.begin(); itr != particleSet.end(); ++itr)
                (*itr)->update(TimePerFrame);
        }

        // measure performance

        updateText.setString("FPS: " + std::to_string(static_cast<int>(1.f / deltaTime.asSeconds())));

        for (auto itr = particleSet.begin(); itr != particleSet.end(); ++itr)
        {
            qTree.addEntity(*itr);
        }

        qTree.checkCollisions();

        for (auto itr = particleSet.begin(); itr != particleSet.end(); ++itr)
        {
            if ((*itr)->isColliding == true)
                (*itr)->mParticle.setFillColor(sf::Color::Red);
            else
                (*itr)->mParticle.setFillColor(sf::Color::Green);

            (*itr)->draw(window);
            (*itr)->isColliding = false;
        }

        qTree.draw(window);
        window.draw(updateText);
        window.display();
    }

    return 0;
}
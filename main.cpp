#include "QuadTree.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Particle.hpp"

int main()
{
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    int width = 700;
    int height = 700;
    float adjust = 1.f;
    int maxVelocity = 200;

    sf::RenderWindow window(sf::VideoMode(width, height), "Quad Tree Example");

    sf::Vector2f position = sf::Vector2f(width * (1.f - adjust) / 2.f, height * (1.f - adjust) / 2.f);
    sf::Vector2f size = sf::Vector2f(width * adjust, height * adjust);

    QuadTree qTree(position, size, 5);

    std::vector<Particle> particleSet;

    sf::Clock clock;

    std::srand(std::time(nullptr));

    for (int i = 0; i < 50; ++i)
    {
        // generate random position

        float xPosition = rand() % width;
        float yPosition = rand() % height;

        // generate random velocity

        float xVelocity = rand() % maxVelocity;
        float yVelocity = rand() % maxVelocity;

        // create the particle and add to the quad tree

        Particle particle(sf::Vector2f(xPosition, yPosition));

        particle.setVelocity(xVelocity, yVelocity);

        particleSet.push_back(particle);

        //std::cout << particleSet.size() << std::endl;
    }

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;

        QuadTree qTree(position, size, 5);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            // {
            //     Particle particle(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            //     qTree.addEntity(particle);
            // }
        }

        window.clear(sf::Color::White);

        timeSinceLastUpdate += deltaTime;

        // while (timeSinceLastUpdate > TimePerFrame)
        // {
        //     timeSinceLastUpdate -= TimePerFrame;

            for (auto itr = particleSet.begin(); itr < particleSet.end(); ++itr)
            {
                itr->update(deltaTime);
                window.draw(itr->mParticle);
                qTree.addEntity(*itr);
            }
        // }

        window.draw(qTree);
        window.display();
    }

    return 0;
}
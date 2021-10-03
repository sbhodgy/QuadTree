#include "QuadTree.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Particle.hpp"

int main()
{

    int width = 700;
    int height = 700;

    sf::RenderWindow window(sf::VideoMode(width, height), "Quad Tree Example");

    float adjust = 0.8f;

    sf::Vector2f position = sf::Vector2f(width * (1.f - adjust) / 2.f, height * (1.f - adjust) / 2.f);
    sf::Vector2f size = sf::Vector2f(width * adjust, height * adjust);

    QuadTree qTree(position, size, 5);

    // std::srand(std::time(nullptr));

    // for (int i = 0; i < 100; i++)
    // {
    //     // generate random location within the quad tree

    //     float xPosition = (rand() % width);
    //     float yPosition = (rand() % height);

    //     // std::cout << xPosition << " " << yPosition << std::endl;

    //     // create the particle and add to the quad tree

    //     Particle particle(sf::Vector2f(xPosition, yPosition));

    //     qTree.addEntity(particle);
    // }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Particle particle(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
                qTree.addEntity(particle);
            }
        }

        // qTree.addEntity()

        window.clear(sf::Color::White);
        window.draw(qTree);
        window.display();
    }

    return 0;
}
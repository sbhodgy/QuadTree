#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Vector2f position, float size);

    void setVelocity(float vx, float vy);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

public:
    sf::RectangleShape mParticle;
    sf::Vector2f mVelocity;
    bool isColliding;
};

#endif // PARTICLE_HPP
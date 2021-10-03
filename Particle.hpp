#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Vector2f position);

    void setVelocity(float vx, float vy);

    void update(sf::Time dt);

public:
    sf::RectangleShape mParticle;
    sf::Vector2f mVelocity;
};

#endif // PARTICLE_HPP
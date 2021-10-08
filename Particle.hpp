#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Asset.hpp"

#include <SFML/Graphics.hpp>

class Particle : public Asset
{
public:
    Particle(sf::Vector2f position, float size);

    void setVelocity(float vx, float vy);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds();

private:
    sf::RectangleShape mParticle;
    sf::Vector2f mVelocity;
};

#endif // PARTICLE_HPP
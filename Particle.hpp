#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle //: public sf::Drawable
{
public:
    Particle(sf::Vector2f position);

public:
    sf::RectangleShape mParticle;
};

#endif // PARTICLE_HPP
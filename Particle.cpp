#include "Particle.hpp"

Particle::Particle(sf::Vector2f position)
    : mParticle(sf::Vector2f(5.f, 5.f))
{
    mParticle.setPosition(position);
    mParticle.setFillColor(sf::Color::Red);
}
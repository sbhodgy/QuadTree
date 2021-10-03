#include "Particle.hpp"

Particle::Particle(sf::Vector2f position)
    : mParticle(sf::Vector2f(5.f, 5.f))
{
    mParticle.setPosition(position);
    mParticle.setFillColor(sf::Color::Red);
}

void Particle::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Particle::update(sf::Time dt)
{
    float xPosition = mParticle.getPosition().x + mVelocity.x * dt.asSeconds();
    float yPosition = mParticle.getPosition().y + mVelocity.y * dt.asSeconds();

    if (xPosition >= 0 && xPosition <= 700.f)
        mParticle.setPosition(sf::Vector2f(xPosition, mParticle.getPosition().y));
    else
        mVelocity.x = -mVelocity.x;

    if (yPosition >= 0 && yPosition <= 700.f)
        mParticle.setPosition(sf::Vector2f(mParticle.getPosition().x, yPosition));
    else
        mVelocity.y = -mVelocity.y;
}
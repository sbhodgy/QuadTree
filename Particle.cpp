#include "Particle.hpp"

Particle::Particle(sf::Vector2f position, float size)
    : mParticle(sf::Vector2f(size, size)),
      isColliding(false)
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

    if (xPosition >= 0 && xPosition <= 700.f - mParticle.getSize().x)
        mParticle.setPosition(sf::Vector2f(xPosition, mParticle.getPosition().y));
    else
        mVelocity.x = -mVelocity.x;

    if (yPosition >= 0 && yPosition <= 700.f - mParticle.getSize().y)
        mParticle.setPosition(sf::Vector2f(mParticle.getPosition().x, yPosition));
    else
        mVelocity.y = -mVelocity.y;
}

void Particle::draw(sf::RenderWindow &window)
{
    // if (isColliding == true)
    //     mParticle.setFillColor(sf::Color::Red);
    // else
    //     mParticle.setFillColor(sf::Color::Green);
    window.draw(mParticle);

    isColliding = false;
}
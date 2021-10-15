#include "Entity.hpp"

Entity::Entity(sf::Vector2f position, float size)
{
    mEntity.setSize(sf::Vector2f(size, size));
    mEntity.setPosition(position);
    mEntity.setFillColor(sf::Color::Red);
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

sf::Vector2f Entity::getVelocity()
{
    return mVelocity;
}

void Entity::update(sf::Time dt)
{
    float xPosition = mEntity.getPosition().x + mVelocity.x * dt.asSeconds();
    float yPosition = mEntity.getPosition().y + mVelocity.y * dt.asSeconds();

    if (xPosition >= 0 && xPosition <= 700.f - mEntity.getSize().x)
        mEntity.setPosition(sf::Vector2f(xPosition, mEntity.getPosition().y));
    else
        mVelocity.x = -mVelocity.x;

    if (yPosition >= 0 && yPosition <= 700.f - mEntity.getSize().y)
        mEntity.setPosition(sf::Vector2f(mEntity.getPosition().x, yPosition));
    else
        mVelocity.y = -mVelocity.y;
}

void Entity::draw(sf::RenderWindow &window)
{
    window.draw(mEntity);

    mColliding = false;
}

sf::FloatRect Entity::getBounds()
{
    return mEntity.getGlobalBounds();
}

unsigned int Entity::getAssetType()
{
    return AssetType::Entity;
}

void Entity::setColor(sf::Color color)
{
    mEntity.setFillColor(color);
}

bool Entity::isMoving()
{
    return (mVelocity.x != 0 || mVelocity.y != 0);
}

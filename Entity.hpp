#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Asset.hpp"

#include "AssetType.hpp"

class Entity : public Asset
{
public:
    Entity(sf::Vector2f position, float size);

    void setVelocity(float vx, float vy);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds();

    unsigned int getAssetType();

    void setColor(sf::Color color);

    bool isMoving();

public:
    bool mColliding;

private:
    sf::RectangleShape mEntity;
    sf::Vector2f mVelocity;
};

#endif // PARTICLE_HPP
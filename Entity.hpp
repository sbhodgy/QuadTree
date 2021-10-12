#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
    Entity(sf::Vector2f position, float size);

    void setVelocity(float vx, float vy);

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds();

public:
    bool mColliding;
    sf::RectangleShape mEntity;

private:
    sf::Vector2f mVelocity;
};

#endif // PARTICLE_HPP
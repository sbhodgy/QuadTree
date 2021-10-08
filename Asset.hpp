#ifndef ASSET_HPP
#define ASSET_HPP

#include <SFML/Graphics.hpp>

class Asset
{
public:
    Asset();

    void update(sf::Time dt);

    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds();

public:
    bool mColliding;
};

#endif // ASSET_HPP
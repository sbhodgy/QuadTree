#ifndef ASSET_HPP
#define ASSET_HPP

#include "AssetType.hpp"

#include <SFML/Graphics.hpp>

class Asset
{
    public:
    Asset();

    virtual unsigned int getAssetType();

    virtual void update(sf::Time dt) = 0;

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual sf::FloatRect getBounds() = 0;
};



#endif // ASSET_HPP
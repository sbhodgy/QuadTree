#include "Asset.hpp"


void Asset::update(sf::Time dt)
: mColliding(false)
{
    // nothing at this level
}

void Asset::draw(sf::RenderWindow &window)
{
    // nothing at this level
}

sf::FloatRect Asset::getBounds()
{
    return sf::FloatRect();
}
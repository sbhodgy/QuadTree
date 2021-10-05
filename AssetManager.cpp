#include "AssetManager.hpp"

AssetManager::AssetManager()
    : mQuad(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f))
{
}

void AssetManager::addParticle(Ptr particle)
{
    mParticles.push_back(particle);
}

void AssetManager::update(sf::Time dt)
{
    for (auto itr : mParticles)
    {
        itr->update(dt);
    }
}

void AssetManager::detectCollisions()
{
    // create quad tree object

    // QuadTree quadTree(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f));

    // add particles to the quad tree

    for (auto itr : mParticles)
    {
        mQuad.addEntity(itr);
    }

    mQuad.checkCollisions();
}

void AssetManager::draw(sf::RenderWindow &window)
{
    for (auto itr : mParticles)
    {
        itr->draw(window);
    }

    mQuad.draw(window);
}
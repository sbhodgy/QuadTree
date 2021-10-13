#include "AssetManager.hpp"

AssetManager::AssetManager()
    : mQuad(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f))
{
}

void AssetManager::addEntity(Ptr entity)
{
    mEntities.push_back(entity);
}

void AssetManager::update(sf::Time dt)
{
    for (auto itr : mEntities)
    {
        itr->update(dt);
    }

    buildQuadTree();
}

void AssetManager::buildQuadTree()
{
    // initialise the quad tree

    mQuad = QuadTree(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f));

    // add Entities to the quad tree

    for (auto itr : mEntities)
    {
        mQuad.addEntity(itr);
    }
}

void AssetManager::detectCollisions()
{
    mQuad.checkCollisions();

    for (auto itr : mEntities)
    {
        if (itr->mColliding == true)
            itr->setColor(sf::Color::Red);
        else
            itr->setColor(sf::Color::Green);

        itr->mColliding = false;
    }
}

void AssetManager::draw(sf::RenderWindow &window)
{
    detectCollisions();

    for (auto itr : mEntities)
    {
        itr->draw(window);
    }

    mQuad.draw(window);
}
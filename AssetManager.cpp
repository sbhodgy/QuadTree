#include "AssetManager.hpp"

AssetManager::AssetManager()
    : mQuad(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f))
{
}

void AssetManager::addEntity(Ptr asset)
{
    mAssets.push_back(asset);
}

void AssetManager::update(sf::Time dt)
{
    for (auto itr : mAssets)
    {
        itr->update(dt);
    }

    buildQuadTree();

    detectCollisions();
}

void AssetManager::buildQuadTree()
{
    // initialise the quad tree

    mQuad = QuadTree(sf::Vector2f(0.f, 0.f), sf::Vector2f(700.f, 700.f));

    // add assets to the quad tree

    for (auto itr : mAssets)
    {
        mQuad.addAsset(itr);
    }
}

void AssetManager::detectCollisions()
{
    mQuad.checkCollisions();

    // for (auto itr : mAssets)
    // {
    //     if (itr->mColliding == true)
    //         itr->setColor(sf::Color::Red);
    //     else
    //         itr->setColor(sf::Color::Green);

    //     itr->mColliding = false;
    // }
}

void AssetManager::draw(sf::RenderWindow &window)
{

    for (auto itr : mAssets)
    {
        itr->draw(window);
    }

    mQuad.draw(window);
}
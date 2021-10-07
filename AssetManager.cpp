#include "AssetManager.hpp"

AssetManager::AssetManager()
    : mQuad(sf::Vector2f(200.f, 200.f), sf::Vector2f(300.f, 300.f))
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

    buildQuadTree();
}

void AssetManager::buildQuadTree()
{
    // initialise the quad tree

    mQuad = QuadTree(sf::Vector2f(200.f, 200.f), sf::Vector2f(300.f, 300.f));

    // add particles to the quad tree

    for (auto itr : mParticles)
    {
        mQuad.addEntity(itr);
    }
}

void AssetManager::detectCollisions()
{
    mQuad.checkCollisions();

    for (auto itr : mParticles)
    {
        if (itr->isColliding == true)
            itr->mParticle.setFillColor(sf::Color::Red);
        else
            itr->mParticle.setFillColor(sf::Color::Green);

        itr->isColliding = false;
    }
}

void AssetManager::draw(sf::RenderWindow &window)
{
    // detectCollisions();

    for (auto itr : mParticles)
    {
        itr->draw(window);
    }

    // mQuad.draw(window);
}
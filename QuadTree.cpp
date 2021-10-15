#include "QuadTree.hpp"

#include "Entity.hpp"

QuadTree::QuadTree(sf::Vector2f position, sf::Vector2f size)
    : mAssetLimit(15),
      mQuad(size),
      mDivided(false),
      mMovingAssets(true)
{
    mQuad.setPosition(position);
    mQuad.setFillColor(sf::Color::Transparent);
    mQuad.setOutlineColor(sf::Color::Transparent);
    mQuad.setOutlineThickness(-1.f);
}

void QuadTree::addAsset(assetPtr asset)
{
    if (mDivided == true)
        passAsset(asset);
    else if (mQuad.getGlobalBounds().intersects(dynamic_cast<Entity &>(*asset).getBounds()))
    {
        mAssets.push_back(asset);

        // if (asset->isMoving() == true)
        //     mMovingAssets = true;
    }

    if (mAssets.size() == mAssetLimit)
        divideQuad();
}

void QuadTree::update(sf::Time time)
{
}

void QuadTree::draw(sf::RenderTarget &window)
{

    if (mDivided == true)
    {
        mQuadNorthEast->draw(window);
        mQuadNorthWest->draw(window);
        mQuadSouthWest->draw(window);
        mQuadSouthEast->draw(window);
    }
    else
    {
        // if (mMovingAssets == true)
        mQuad.setOutlineColor(sf::Color::Red);

        window.draw(mQuad);
    }
}

void QuadTree::passAsset(assetPtr asset)
{
    // pass the asset to the children quads.
    // the children will check for inclusion / exclusion

    mQuadNorthEast->addAsset(asset);
    mQuadNorthWest->addAsset(asset);
    mQuadSouthWest->addAsset(asset);
    mQuadSouthEast->addAsset(asset);
}

void QuadTree::divideQuad()
{
    // create variables to store the position and size of the current quad

    float x = mQuad.getPosition().x;
    float y = mQuad.getPosition().y;
    float w = mQuad.getSize().x;
    float h = mQuad.getSize().y;

    // create new quad objects and assign to the shared pointer variables

    mQuadNorthEast = quadPtr(new QuadTree(sf::Vector2f(x + w / 2.f, y), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadNorthWest = quadPtr(new QuadTree(sf::Vector2f(x, y), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadSouthWest = quadPtr(new QuadTree(sf::Vector2f(x, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadSouthEast = quadPtr(new QuadTree(sf::Vector2f(x + w / 2.f, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f)));

    // pass assets in the current quad to the children quads

    for (auto itr = mAssets.begin(); itr != mAssets.end(); ++itr)
    {
        passAsset(*itr);
    }

    // remove assets from the current quad

    mAssets.clear();

    // flag that the current quad has been divided

    mDivided = true;
    mMovingAssets = false;
}

void QuadTree::checkCollisions()
{
    if (mDivided == true)
    {
        mQuadNorthEast->checkCollisions();
        mQuadNorthWest->checkCollisions();
        mQuadSouthWest->checkCollisions();
        mQuadSouthEast->checkCollisions();
    }
    else if (mMovingAssets == true)
    {
        for (auto itr1 = mAssets.begin(); itr1 != mAssets.end(); ++itr1)
        {
            for (auto itr2 = std::next(itr1, 1); itr2 != mAssets.end(); ++itr2)
            {
                if ((*itr1)->getBounds().intersects((*itr2)->getBounds()))
                {
                    dynamic_cast<Entity&>(*(*itr1)).setColor(sf::Color::Green);
                    dynamic_cast<Entity&>(*(*itr1)).setVelocity(-(dynamic_cast<Entity&>(*(*itr1)).getVelocity()));
                    dynamic_cast<Entity&>(*(*itr2)).setVelocity(-(dynamic_cast<Entity&>(*(*itr2)).getVelocity()));
                }
            }
        }
    }
}
#include "QuadTree.hpp"

QuadTree::QuadTree(sf::Vector2f position, sf::Vector2f size)
    : mEntityLimit(5),
      mQuad(size),
      mDivided(false),
      mMinQuadSize(5.f)
{
    mQuad.setPosition(position);
    mQuad.setFillColor(sf::Color::Transparent);
    mQuad.setOutlineColor(sf::Color::White);
    mQuad.setOutlineThickness(-1.f);
}

void QuadTree::draw(sf::RenderTarget &window)
{
    window.draw(mQuad);

    if (mDivided == true)
    {
        mQuadNorthEast->draw(window);
        mQuadNorthWest->draw(window);
        mQuadSouthWest->draw(window);
        mQuadSouthEast->draw(window);
    }
}

void QuadTree::addEntity(std::shared_ptr<Particle> particle)
{
    if (mDivided == true)
        passEntity(particle);
    else if (mQuad.getGlobalBounds().intersects(particle->mParticle.getGlobalBounds()))
        mEntities.push_back(particle);

    if (mEntities.size() == mEntityLimit && (mQuad.getSize().x / 2.f) >= mMinQuadSize)
        divideQuad();
}

void QuadTree::passEntity(std::shared_ptr<Particle> particle)
{
    mQuadNorthEast->addEntity(particle);
    mQuadNorthWest->addEntity(particle);
    mQuadSouthWest->addEntity(particle);
    mQuadSouthEast->addEntity(particle);
}

void QuadTree::divideQuad()
{
    float x = mQuad.getPosition().x;
    float y = mQuad.getPosition().y;
    float w = mQuad.getSize().x;
    float h = mQuad.getSize().y;

    mQuadNorthEast = Ptr(new QuadTree(sf::Vector2f(x + w / 2.f, y), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadNorthWest = Ptr(new QuadTree(sf::Vector2f(x, y), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadSouthWest = Ptr(new QuadTree(sf::Vector2f(x, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f)));
    mQuadSouthEast = Ptr(new QuadTree(sf::Vector2f(x + w / 2.f, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f)));

    for (auto itr = mEntities.begin(); itr != mEntities.end(); ++itr)
    {
        passEntity(*itr);
    }

    mEntities.clear();

    mDivided = true;
}

void QuadTree::checkCollisions()
{
    for (auto itr1 = mEntities.begin(); itr1 != mEntities.end(); ++itr1)
    {
        //(*itr1)->isColliding = false;

        for (auto itr2 = std::next(itr1, 1); itr2 != mEntities.end(); ++itr2)
        {
            if ((*itr1)->mParticle.getGlobalBounds().intersects((*itr2)->mParticle.getGlobalBounds()))
            {
                 (*itr1)->isColliding = true;
                 (*itr2)->isColliding = true;
            }
        }
    }

    if (mDivided == true)
    {
        mQuadNorthEast->checkCollisions();
        mQuadNorthWest->checkCollisions();
        mQuadSouthWest->checkCollisions();
        mQuadSouthEast->checkCollisions();
    }
}

void QuadTree::clear()
{
    if(mDivided == true)
    {
        // delete &mQuadNorthEast;
    }
    else
    {
        // delete this;
    }
}

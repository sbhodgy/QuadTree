#include "QuadTree.hpp"

QuadTree::QuadTree(sf::Vector2f position, sf::Vector2f size, size_t entityLimit)
    : mEntityLimit(entityLimit),
      mQuad(size),
      mDivided(false),
      mMinQuadSize(5.f)
{
    mQuad.setPosition(position);
    mQuad.setFillColor(sf::Color::Transparent);
    mQuad.setOutlineColor(sf::Color::Black);
    mQuad.setOutlineThickness(-1.f);
}

void QuadTree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mQuad, states);

    // for (auto itr = mEntities.begin(); itr < mEntities.end(); ++itr)
    // {
    //     target.draw(itr->mParticle, states);
    // }

    if (mDivided == true)
    {
        mQuadNorthEast->draw(target, states);
        mQuadNorthWest->draw(target, states);
        mQuadSouthWest->draw(target, states);
        mQuadSouthEast->draw(target, states);
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

    mQuadNorthEast = Ptr(new QuadTree(sf::Vector2f(x + w / 2.f, y), sf::Vector2f(w / 2.f, h / 2.f), mEntityLimit));
    mQuadNorthWest = Ptr(new QuadTree(sf::Vector2f(x, y), sf::Vector2f(w / 2.f, h / 2.f), mEntityLimit));
    mQuadSouthWest = Ptr(new QuadTree(sf::Vector2f(x, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f), mEntityLimit));
    mQuadSouthEast = Ptr(new QuadTree(sf::Vector2f(x + w / 2.f, y + h / 2.f), sf::Vector2f(w / 2.f, h / 2.f), mEntityLimit));

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

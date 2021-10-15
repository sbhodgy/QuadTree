#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class QuadTree
{
    typedef std::unique_ptr<QuadTree> Ptr;

    typedef std::shared_ptr<Asset> assetPtr;

public:
    QuadTree(sf::Vector2f position, sf::Vector2f size);

    void addEntity(assetPtr entity);

    void draw(sf::RenderTarget &target);

    void checkCollisions();

private:
    void passEntity(assetPtr entity);

    void divideQuad();

private:
    std::vector<assetPtr> mEntities;
    sf::RectangleShape mQuad;
    float mMinQuadSize;
    size_t mEntityLimit;
    bool mDivided;
    bool mMovingEntities;

    // pointer to the four new
    Ptr mQuadNorthEast;
    Ptr mQuadNorthWest;
    Ptr mQuadSouthEast;
    Ptr mQuadSouthWest;
};

#endif // QUADTREE_HPP
#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class QuadTree
{
    typedef std::unique_ptr<QuadTree> Ptr;

public:
    QuadTree(sf::Vector2f position, sf::Vector2f size);

    void addEntity(std::shared_ptr<Entity> entity);

    void draw(sf::RenderTarget &target);

    void checkCollisions();

private:
    void passEntity(std::shared_ptr<Entity> entity);

    void divideQuad();

private:
    std::vector<std::shared_ptr<Entity>> mEntities;
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
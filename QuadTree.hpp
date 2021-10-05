#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Particle.hpp"

class QuadTree
{
    typedef std::unique_ptr<QuadTree> Ptr;

public:
    QuadTree(sf::Vector2f position, sf::Vector2f size);

    void addEntity(std::shared_ptr<Particle> particle);

    void draw(sf::RenderTarget &target);

    void checkCollisions();

    void clear();

private:
    void passEntity(std::shared_ptr<Particle> particle);

    void divideQuad();

private:
    std::vector<std::shared_ptr<Particle>> mEntities;
    sf::RectangleShape mQuad;
    float mMinQuadSize;
    size_t mEntityLimit;
    bool mDivided;

    // pointer to the four new
    Ptr mQuadNorthEast;
    Ptr mQuadNorthWest;
    Ptr mQuadSouthEast;
    Ptr mQuadSouthWest;
};

#endif // QUADTREE_HPP
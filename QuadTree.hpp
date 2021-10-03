#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Particle.hpp"

class QuadTree : public sf::Drawable
{
    typedef std::unique_ptr<QuadTree> Ptr;

public:
    QuadTree(sf::Vector2f position, sf::Vector2f size, int entityLimit);

    void addEntity(Particle entity);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void passEntity(Particle particle);

    void divideQuad();

private:
    std::vector<Particle> mEntities;
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
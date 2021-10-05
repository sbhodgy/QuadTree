#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include "QuadTree.hpp"

#include <memory>

class AssetManager
{
    typedef std::shared_ptr<Particle> Ptr;

public:
    AssetManager();

    void addParticle(Ptr particle);

    void update(sf::Time dt);

    void detectCollisions();

    void draw(sf::RenderWindow &window);

private:
private:
    std::vector<Ptr> mParticles;
    QuadTree mQuad;
};

#endif // ASSETMANAGER_HPP
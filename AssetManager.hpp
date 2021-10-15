#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include "QuadTree.hpp"

#include "Entity.hpp"

#include <memory>

class AssetManager
{
    typedef std::shared_ptr<Asset> Ptr;

public:
    AssetManager();

    void addEntity(Ptr entity);

    void update(sf::Time dt);

    void detectCollisions();

    void draw(sf::RenderWindow &window);

private:
    void buildQuadTree();

private:
    std::vector<Ptr> mEntities;
    QuadTree mQuad;
};

#endif // ASSETMANAGER_HPP
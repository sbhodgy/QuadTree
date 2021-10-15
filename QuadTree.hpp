#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Asset.hpp"

class QuadTree
{
    typedef std::unique_ptr<QuadTree> quadPtr;

    typedef std::shared_ptr<Asset> assetPtr;

public:
    QuadTree(sf::Vector2f position, sf::Vector2f size);

    void addAsset(assetPtr asset);

    void draw(sf::RenderTarget &target);

    void checkCollisions();

    void flockAssets();

private:
    void passAsset(assetPtr asset);

    void divideQuad();

private:
    std::vector<assetPtr> mAssets;
    sf::RectangleShape mQuad;
    float mMinQuadSize;
    size_t mAssetLimit;
    bool mDivided;
    bool mMovingAssets;

    // pointer to the four new
    quadPtr mQuadNorthEast;
    quadPtr mQuadNorthWest;
    quadPtr mQuadSouthEast;
    quadPtr mQuadSouthWest;
};

#endif // QUADTREE_HPP
#ifndef ASSET_HPP
#define ASSET_HPP

#include "AssetType.hpp"

class Asset
{
    public:
    Asset();

    virtual unsigned int getAssetType();
};



#endif // ASSET_HPP
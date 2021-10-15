#ifndef ASSETTYPE_HPP
#define ASSETTYPE_HPP

namespace AssetType
{
    enum
    {
        None = 0,
        Asset = 1 << 0,
        Tile = 1 << 1,
        Entity = 1 << 2,
    };
};

#endif // ASSETTYPE_HPP
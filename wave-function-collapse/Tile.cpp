#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(TileType input)
{
    type = input;
}

bool Tile::operator==(const Tile& other) const
{
    return type == other.type;
}

bool Tile::operator<(const Tile& other) const
{
    return static_cast<int>(type) < static_cast<int>(other.type);
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
    switch (tile.type) {
    case TileType::EMPTY:
        os << "EMPTY";
        break;
    case TileType::GRASS:
        os << "GRASS";
        break;
    case TileType::WATER:
        os << "WATER";
        break;
    case TileType::BEACH:
        os << "BEACH";
        break;
        // Add more cases as needed
    default:
        os << "Unknown TileType";
    }
    return os;
}

Tile operator&(const Tile& lhs, const Tile& rhs)
{
    return Tile(static_cast<TileType>(static_cast<int>(lhs.type) & static_cast<int>(rhs.type)));
}

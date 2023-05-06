#include "Tile.h"

Tile::Tile(bool walkable) : walkable(walkable) {}

bool Tile::IsWalkable() const {
    return walkable;
}
#pragma once

class Tile {
public:
    Tile(bool walkable);

    bool IsWalkable() const;

private:
    bool walkable;
};
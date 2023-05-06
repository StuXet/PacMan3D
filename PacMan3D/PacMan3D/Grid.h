#include <vector>
#include "raylib.h"

class Grid {
public:
    Grid(const std::vector<std::vector<int>>& mapLayout, float cellSize);

    bool IsWalkable(int x, int y) const;
    Vector2 GetGridDimensions() const;

private:
    std::vector<std::vector<int>> map;
    float cellSize;
};
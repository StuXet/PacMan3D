#include "Grid.h"

Grid::Grid(const std::vector<std::vector<int>>& mapLayout, float cellSize)
    : map(mapLayout), cellSize(cellSize) {}

bool Grid::IsWalkable(int x, int y) const {
    if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size()) {
        return false;
    }
    return map[y][x] == 0;
}

Vector2 Grid::GetGridDimensions() const {
    return Vector2{ (float)map[0].size(), (float)map.size() };
}
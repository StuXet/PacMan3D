#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include "raylib.h"

inline bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

inline bool operator!=(const Vector2& lhs, const Vector2& rhs) {
    return !(lhs == rhs);
}

struct Vector2Hash {
    size_t operator()(const Vector2& vec) const {
        return std::hash<float>()(vec.x) ^ (std::hash<float>()(vec.y) << 1);
    }
};

struct Node {
    Vector2 position;
    float cost;
    float heuristic;
    Node* parent;
};

struct NodeComparator {
    bool operator()(const Node* a, const Node* b) const {
        return (a->cost + a->heuristic) > (b->cost + b->heuristic);
    }
};

float Heuristic(Vector2 a, Vector2 b);

std::vector<Vector2> AStarPathfinding(int** mapLayout, int mapWidth, int mapHeight, Vector2 start, Vector2 goal);

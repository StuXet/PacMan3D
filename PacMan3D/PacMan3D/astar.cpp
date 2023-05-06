#include "astar.h"

float Heuristic(Vector2 a, Vector2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Vector2> AStarPathfinding(int** mapLayout, int mapWidth, int mapHeight, Vector2 start, Vector2 goal) {
    std::unordered_map<Vector2, Node, Vector2Hash> nodes;
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> openList;

    Node* startNode = &nodes[start];
    startNode->position = start;
    startNode->cost = 0;
    startNode->heuristic = Heuristic(start, goal);
    startNode->parent = nullptr;

    openList.push(startNode);

    std::vector<Vector2> directions = {
        { 1, 0 },
        { -1, 0 },
        { 0, 1 },
        { 0, -1 }
    };

    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        if (currentNode->position == goal) {
            std::vector<Vector2> path;
            Node* node = currentNode;
            while (node) {
                path.push_back(node->position);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Vector2& direction : directions) {
            Vector2 newPos = currentNode->position + direction;

            if (newPos.x < 0 || newPos.y < 0 || newPos.x >= mapWidth || newPos.y >= mapHeight || mapLayout[(int)newPos.y][(int)newPos.x] == 1) {
                continue;
            }

            Node* neighborNode = &nodes[newPos];
            if (neighborNode->parent != nullptr) {
                continue;
            }

            neighborNode->position = newPos;
            neighborNode->cost = currentNode->cost + 1;
            neighborNode->heuristic = Heuristic(newPos, goal);
            neighborNode->parent = currentNode;

            openList.push(neighborNode);
        }
    }

    return {};  // No path found
}
#include "raylib.h"

class Wall {
public:
    Wall(const Vector3& position, const Vector3& size, Color color);

    void Draw() const;
    BoundingBox GetBoundingBox() const;

private:
    Vector3 position;
    Vector3 size;
    Color color;
};
#include "raylib.h"

class PointCube {
public:
    PointCube(const Vector3& position, float size, Color color);

    void Draw() const;
    BoundingBox GetBoundingBox() const;
    void SetActive(bool active);
    bool IsActive() const;

private:
    Vector3 position;
    float size;
    Color color;
    bool active;
};
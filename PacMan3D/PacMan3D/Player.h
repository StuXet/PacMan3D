#include "raylib.h"

class Player {
public:
    Player(Vector3 position, float radius, Color color);

    void Update();
    void Draw() const;
    BoundingBox GetBoundingBox() const;
    Vector3 GetPosition() const;
    void ResetPosition();
    void SetColor(Color color);

private:
    Vector3 position;
    Vector3 previousPosition;
    float radius;
    Color color;
};
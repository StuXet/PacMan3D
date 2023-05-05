#include "raylib.h"

class Player {
public:
    Player(Vector3 position, float radius, Color color);

    void Update();
    void Draw() const;
    void SetColor(Color color);
    BoundingBox GetBoundingBox() const;
    void ResetPosition();
    Vector3 GetPosition() const;

private:
    Vector3 position;
    Vector3 previousPosition;
    float radius;
    Color color;
};
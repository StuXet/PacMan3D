#include <vector>

#include "raylib.h"

class Enemy {
public:
    Enemy(Vector3 position, float radius, Color color);

    void Update(const Vector3& target, const int mapLayout[][21]);
    void Draw() const;
    void SetSpeed(float newSpeed);
    Vector3 GetPosition() const;
    float GetRadius() const;

private:
    float radius;
    Color color;
    float speed;
    Vector3 position;
};
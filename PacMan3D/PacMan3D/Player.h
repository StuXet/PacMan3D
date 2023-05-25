#pragma once
#include "Enemy.h"
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
    void SetSpeed(float newSpeed);
    float GetRadius() const;
    bool powerEaten = false;
    float powerEatenTime = 0.0f;
    float powerDuration = 10.0f;
    void EatPower();

private:
    Vector3 position;
    Vector3 previousPosition;
    float radius;
    float speed;
    Color color;
};
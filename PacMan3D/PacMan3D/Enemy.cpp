#include "Enemy.h"
#include <raymath.h>

Enemy::Enemy(Vector3 position, float radius, Color color)
    : position(position), radius(radius), color(color), speed(0.1f) {}

void Enemy::Update(const Vector3& target, const int mapLayout[][21])
{
    Vector3 direction = Vector3Subtract(target, position);
    float distance = Vector3Length(direction);

    if (distance > 0.0f) {
        direction = Vector3Scale(direction, 1.0f / distance); // Normalize direction
        position = Vector3Add(position, Vector3Scale(direction, speed));
    }
}


void Enemy::Draw() const {
    DrawSphere(position, radius, color);
}

void Enemy::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

Vector3 Enemy::GetPosition() const {
    return position;
}

float Enemy::GetRadius() const {
    return radius;
}
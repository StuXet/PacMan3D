#include "Player.h"

Player::Player(Vector3 position, float radius, Color color)
    : position(position), previousPosition(position), radius(radius), color(color), speed(0.2f) {}

void Player::Update() {
    previousPosition = position;

    if (IsKeyDown(KEY_RIGHT))
        position.x += speed;
    else if (IsKeyDown(KEY_LEFT))
        position.x -= speed;
    else if (IsKeyDown(KEY_DOWN))
        position.z += speed;
    else if (IsKeyDown(KEY_UP))
        position.z -= speed;
}

void Player::Draw() const {
    DrawSphere(position, radius, color);
}

BoundingBox Player::GetBoundingBox() const {
    return
	{
        Vector3
		{
            position.x - radius,
            position.y - radius,
            position.z - radius
        },
        Vector3
		{
            position.x + radius,
            position.y + radius,
            position.z + radius
        }
    };
}

Vector3 Player::GetPosition() const {
    return position;
}

void Player::ResetPosition() {
    position = previousPosition;
}

void Player::SetColor(Color newColor) {
    color = newColor;
}

void Player::SetSpeed(float newSpeed) {
    speed = newSpeed;
}


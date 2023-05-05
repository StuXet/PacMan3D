#include "Player.h"

Player::Player(Vector3 position, float radius, Color color)
    : position(position), previousPosition(position), radius(radius), color(color) {}

void Player::Update()
{
    previousPosition = position;

    if (IsKeyDown(KEY_RIGHT))
        position.x += 0.2f;
    else if (IsKeyDown(KEY_LEFT))
        position.x -= 0.2f;
    else if (IsKeyDown(KEY_DOWN))
        position.z += 0.2f;
    else if (IsKeyDown(KEY_UP))
        position.z -= 0.2f;
}

void Player::Draw() const {
    DrawSphere(position, radius, color);
}

void Player::SetColor(Color newColor)
{
    color = newColor;
}

BoundingBox Player::GetBoundingBox() const
{
    BoundingBox box;
    box.min = { position.x - radius, position.y - radius, position.z - radius };
    box.max = { position.x + radius, position.y + radius, position.z + radius };
    return box;
}

void Player::ResetPosition()
{
    position = previousPosition;
}

Vector3 Player::GetPosition() const
{
	return position;
}

#include "Enemy.h"
#include <raymath.h>


Enemy::Enemy(Vector3 position, float radius, Color color)
	: position(position), radius(radius), color(color), previousPosition(position), speed(0.1f), respawnPosition({ 10.0f, 0.5f, 10.0f }) {}

void Enemy::Update(const Vector3& target, const int mapLayout[][21])
{
	previousPosition = position;
	Vector3 direction = Vector3Subtract(target, position);
	float distance = Vector3Length(direction);

	if (distance > 0.0f) {
		direction = Vector3Scale(direction, 1.0f / distance); // Normalize direction
		position = Vector3Add(position, Vector3Scale(direction, speed));
	}
}


void Enemy::Draw() const {
	if (active)
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

void Enemy::SetActive(bool isActive) {
	active = isActive;
}

bool Enemy::IsActive() {
	return active;
}

void Enemy::Respawn()
{
	position = respawnPosition;
	active = true;
}

void Enemy::ResetPosition()
{
	position = previousPosition;
}

BoundingBox Enemy::GetBoundingBox() const
{
	{
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

}

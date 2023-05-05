#include "PointCube.h"

PointCube::PointCube(const Vector3& position, float size, Color color)
	: position(position), size(size), color(color), active(true) {}

void PointCube::Draw() const
{
	if (active) {
		DrawCube(position, size, size, size, color);
	}
}

BoundingBox PointCube::GetBoundingBox() const
{
	return
	{
		Vector3{position.x - size / 2, position.y - size / 2, position.z - size / 2},
		Vector3{position.x + size / 2, position.y + size / 2, position.z + size / 2}
	};
}

void PointCube::SetActive(bool active)
{
	this->active = active;
}

bool PointCube::IsActive() const
{
	return active;
}
#include "Wall.h"

Wall::Wall(const Vector3& position, const Vector3& size, Color color)
    : position(position), size(size), color(color) {}

void Wall::Draw() const
{
    DrawCube(position, size.x, size.y, size.z, color);
    DrawCubeWires(position, size.x, size.y, size.z, DARKGRAY);
}

BoundingBox Wall::GetBoundingBox() const
{
    return
	{
        Vector3
    	{
            position.x - size.x / 2,
            position.y - size.y / 2,
            position.z - size.z / 2
        },
        Vector3
    	{
            position.x + size.x / 2,
            position.y + size.y / 2,
            position.z + size.z / 2
        }
    };
}
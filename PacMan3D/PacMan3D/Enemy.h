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
	bool active = true;
	void SetActive(bool isActive);
	bool IsActive();
	void Respawn();
	void ResetPosition();
	BoundingBox GetBoundingBox() const;


private:
	Vector3 previousPosition;
	float radius;
	Color color;
	float speed;
	Vector3 position;
	Vector3 respawnPosition;
};
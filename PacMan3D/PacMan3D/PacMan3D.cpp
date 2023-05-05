#include "raylib.h"
#include "Player.h"
#include "PointCube.h"

int main(void) {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - box collisions");

	// Define the camera to look into our 3D world
	Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

	Vector3 playerPosition = { 0.0f, 1.0f, 2.0f };
	float playerRadius = 0.5f;
	Color playerColor = YELLOW;

	Player player(playerPosition, playerRadius, playerColor);

	Vector3 leftWallPos = { -10.5f, 0.5f, 0.0f };
	Vector3 lefyWallSize = { 1.0f, 1.0f, 20.0f };

	Vector3 topWallPos = { 0.0f, 0.5f, -10.5f };
	Vector3 topWallSize = { 20.0f, 1.0f, 1.0f };

	bool collision = false;

	int score = 0;
	PointCube pointCube({ 5.0f, 0.5f, 0.0f }, 1.0f, WHITE);


	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) {
		// Update
		//----------------------------------------------------------------------------------

		// Update player
		player.Update();

		collision = false;

		BoundingBox playerBox = player.GetBoundingBox();

		BoundingBox leftWallBox{
			Vector3{
				leftWallPos.x - lefyWallSize.x / 2,
				leftWallPos.y - lefyWallSize.y / 2,
				leftWallPos.z - lefyWallSize.z / 2
			},
			Vector3{
				leftWallPos.x + lefyWallSize.x / 2,
				leftWallPos.y + lefyWallSize.y / 2,
				leftWallPos.z + lefyWallSize.z / 2
			}
		};

		BoundingBox topWallBox{
			Vector3{
				topWallPos.x - topWallSize.x / 2,
				topWallPos.y - topWallSize.y / 2,
				topWallPos.z - topWallSize.z / 2
			},
			Vector3{
				topWallPos.x + topWallSize.x / 2,
				topWallPos.y + topWallSize.y / 2,
				topWallPos.z + topWallSize.z / 2
			}
		};

		if (CheckCollisionBoxes(playerBox, leftWallBox) || CheckCollisionBoxes(playerBox, topWallBox)) {
			collision = true;
			player.ResetPosition();
		}

		player.SetColor(collision ? RED : YELLOW);

		if (!collision && pointCube.IsActive() && CheckCollisionBoxes(playerBox, pointCube.GetBoundingBox())) {
			pointCube.SetActive(false);
			score++;
		}

		// Update camera position and target
		Vector3 playerPos = player.GetPosition();
		camera.position.x = playerPos.x + 0.0f;
		camera.position.y = playerPos.y + 5.0f;
		camera.position.z = playerPos.z + 10.0f;
		camera.target = playerPos;

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		pointCube.Draw();

		// Draw enemy-box
		DrawCube(leftWallPos, lefyWallSize.x, lefyWallSize.y, lefyWallSize.z, GRAY);
		DrawCubeWires(leftWallPos, lefyWallSize.x, lefyWallSize.y, lefyWallSize.z, DARKGRAY);

		// Draw top wall
		DrawCube(topWallPos, topWallSize.x, topWallSize.y, topWallSize.z, GRAY);
		DrawCubeWires(topWallPos, topWallSize.x, topWallSize.y, topWallSize.z, DARKGRAY);

		// Draw player
		player.Draw();

		DrawGrid(20, 1.0f);        // Draw a grid

		EndMode3D();

		DrawText("Move player with cursors to collide", 220, 40, 20, GRAY);
		DrawText(TextFormat("Score: %d", score), 10, 40, 20, GRAY);

		DrawFPS(10, 10);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

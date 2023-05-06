#include <vector>
#include "Ghost.h"
#include "raylib.h"
#include "Player.h"
#include "PointCube.h"
#include "Wall.h"


int main(void) {

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [models] example - box collisions");

	// Define the camera to look into our 3D world
	Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

	Vector3 playerPosition = { 1.0f, 1.0f, 2.0f };
	float playerRadius = 0.3f;
	Color playerColor = YELLOW;

	Player player(playerPosition, playerRadius, playerColor);

	player.SetSpeed(0.1f);

	bool collision = false;

	int score = 0;
	PointCube pointCube({ 5.0f, 0.5f, 1.0f }, 1.0f, BLUE);

	/*Wall leftWall({ -10.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 20.0f }, GRAY);
	Wall topWall({ 0.0f, 0.5f, -10.5f }, { 20.0f, 1.0f, 1.0f }, GRAY);
	Wall bottomWall({ 0.0f, 0.5f, 10.5f }, { 20.0f, 1.0f, 1.0f }, GRAY);*/

	//ENEMY
	Enemy enemy({ 10.0f, 0.5f, 10.0f }, 0.3f, RED);
	enemy.SetSpeed(0.08f);


	while (!WindowShouldClose()) 
	{
		float deltaTime = GetFrameTime();

		const int mapWidth = 21;
		const int mapHeight = 21;

		int mapLayout[mapHeight][mapWidth] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		};

		std::vector<Wall> walls;

		const float wallWidth = 1.0f;
		const float wallHeight = 1.0f;
		const float wallDepth = 1.0f;

		for (int i = 0; i < mapHeight; ++i) {
			for (int j = 0; j < mapWidth; ++j) {
				if (mapLayout[i][j] == 1) {
					float x = j * wallWidth;
					float y = wallHeight / 2;
					float z = i * wallDepth;

					walls.emplace_back(Vector3{ x, y, z }, Vector3{ wallWidth, wallHeight, wallDepth }, GRAY);
				}
			}
		}

		SetTargetFPS(60);
		//--------------------------------------------------------------------------------------

		// Main game loop
		while (!WindowShouldClose()) {
			// Update
			//----------------------------------------------------------------------------------

			//ENEMY
			enemy.Update(player.GetPosition(), mapLayout);


			// Update player
			player.Update();

			collision = false;

			BoundingBox playerBox = player.GetBoundingBox();


			/*BoundingBox leftWallBox = leftWall.GetBoundingBox();
			BoundingBox topWallBox = topWall.GetBoundingBox();
			BoundingBox bottomWallBox = bottomWall.GetBoundingBox();*/

			//if (CheckCollisionBoxes(playerBox, leftWallBox) || CheckCollisionBoxes(playerBox, topWallBox) || CheckCollisionBoxes(playerBox, bottomWallBox)) 
			//{
			//	collision = true;
			//	player.ResetPosition(); // Reset player position to the previous frame
			//}

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

			for (const Wall& wall : walls) {
				BoundingBox wallBox = wall.GetBoundingBox();

				if (CheckCollisionBoxes(playerBox, wallBox)) {
					collision = true;
					player.ResetPosition(); // Reset player position to the previous frame
					break;
				}
			}



			// Draw
			//----------------------------------------------------------------------------------
			BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);

			/*leftWall.Draw();
			topWall.Draw();
			bottomWall.Draw();*/

			for (const Wall& wall : walls) {
				wall.Draw();
			}


			pointCube.Draw();

			//ENEMY
			enemy.Draw();


			// Draw player
			player.Draw();

			//DrawGrid(20, 1.0f);        // Draw a grid

			EndMode3D();

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
}
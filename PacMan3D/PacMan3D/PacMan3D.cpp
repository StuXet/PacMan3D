#include <vector>
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
	PointCube powerCube({ 7.0f, 0.5f, 1.0f }, 1.0f, PINK);

	/*Wall leftWall({ -10.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 20.0f }, GRAY);
	Wall topWall({ 0.0f, 0.5f, -10.5f }, { 20.0f, 1.0f, 1.0f }, GRAY);
	Wall bottomWall({ 0.0f, 0.5f, 10.5f }, { 20.0f, 1.0f, 1.0f }, GRAY);*/

	//ENEMY
	Enemy enemy({ 10.0f, 0.5f, 10.0f }, 0.3f, RED);
	enemy.SetSpeed(0.08f);
	bool isDead = false;


	float deltaTime = GetFrameTime();

	const int mapWidth = 21;
	const int mapHeight = 21;

	int mapLayout[mapHeight][mapWidth] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
	std::vector<PointCube> pointCubes;
	std::vector<PointCube> powerCubes;

	const float wallWidth = 1.0f;
	const float wallHeight = 1.0f;
	const float wallDepth = 1.0f;

	for (int i = 0; i < mapHeight; ++i) {
		for (int j = 0; j < mapWidth; ++j) {
			float x = j * wallWidth;
			float y = wallHeight / 2;
			float z = i * wallDepth;

			switch (mapLayout[i][j]) {
			case 1:  // Wall
				walls.emplace_back(Vector3{ x, y, z }, Vector3{ wallWidth, wallHeight, wallDepth }, GRAY);
				break;

			case 2:  // PointCube
				pointCubes.emplace_back(Vector3{ x, y, z }, 1.0f, BLUE);
				break;

			case 3:  // PowerCube
				powerCubes.emplace_back(Vector3{ x, y, z }, 1.0f, PINK);
				break;

			default:
				// Do nothing for empty space
				break;
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
		if (!isDead) {
			player.Update();

			// Move enemy
			enemy.Update(player.GetPosition(), mapLayout);

			// Check for collision between player and enemy
			if (CheckCollisionSpheres(player.GetPosition(), player.GetRadius(), enemy.GetPosition(), enemy.GetRadius()))
			{
				if (player.powerEaten == true)
				{
					//enemy.SetActive(false);
					enemy.Respawn();
				}
				else
				{
					isDead = true;
				}
			}




			// Update player
			//player.Update();

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

			/*if (!collision && pointCube.IsActive() && CheckCollisionBoxes(playerBox, pointCube.GetBoundingBox())) {
				pointCube.SetActive(false);
				score++;
			}

			if (!collision && powerCube.IsActive() && CheckCollisionBoxes(playerBox, powerCube.GetBoundingBox())) {
				powerCube.SetActive(false);
				score++;
				player.EatPower();
			}*/

			for (PointCube& cube : pointCubes) {
				if (!collision && cube.IsActive() && CheckCollisionBoxes(playerBox, cube.GetBoundingBox())) {
					cube.SetActive(false);
					score++;
				}
			}

			for (PointCube& cube : powerCubes) {
				if (!collision && cube.IsActive() && CheckCollisionBoxes(playerBox, cube.GetBoundingBox())) {
					cube.SetActive(false);
					score++;
					player.EatPower();
				}
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


		/*pointCube.Draw();
		powerCube.Draw();*/

		for (const PointCube& cube : pointCubes) {
			cube.Draw();
		}

		for (const PointCube& cube : powerCubes) {
			cube.Draw();
		}

		//ENEMY
		enemy.Draw();


		// Draw player
		player.Draw();

		//DrawGrid(20, 1.0f);        // Draw a grid

		EndMode3D();

		DrawText(TextFormat("Score: %d", score), 10, 40, 20, GRAY);

		if (isDead) {
			DrawText("DEAD", screenWidth / 2 - MeasureText("DEAD", 40) / 2, screenHeight / 2 - 20, 40, RED);
		}


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

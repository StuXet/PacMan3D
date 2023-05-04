#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
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

    Vector3 leftWallPos = { -10.5f, 0.5f, 0.0f };
    Vector3 lefyWallSize = { 1.0f, 1.0f, 20.0f };

    Vector3 topWallPos = { 0.0f, 0.5f, -10.5f };
    Vector3 topWallSize = { 20.0f, 1.0f, 1.0f };


    bool collision = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Move player
        Vector3 previousPlayerPosition = playerPosition;

        if (IsKeyDown(KEY_RIGHT))
            playerPosition.x += 0.2f;
        else if (IsKeyDown(KEY_LEFT))
            playerPosition.x -= 0.2f;
        else if (IsKeyDown(KEY_DOWN))
            playerPosition.z += 0.2f;
        else if (IsKeyDown(KEY_UP))
            playerPosition.z -= 0.2f;

        collision = false;

        bool collision = false;
        BoundingBox playerBox{
            Vector3{
                playerPosition.x - playerRadius,
                playerPosition.y - playerRadius,
                playerPosition.z - playerRadius
            },
            Vector3{
                playerPosition.x + playerRadius,
                playerPosition.y + playerRadius,
                playerPosition.z + playerRadius
            }
        };
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
            playerPosition = previousPlayerPosition; // Reset player position to the previous frame
        }
        playerColor = collision ? RED : YELLOW;

        // Update camera position and target
        // Update camera position and target
        camera.position.x = playerPosition.x + 0.0f;
        camera.position.y = playerPosition.y + 5.0f;
        camera.position.z = playerPosition.z + 10.0f;
        camera.target = playerPosition;


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw enemy-box
        DrawCube(leftWallPos, lefyWallSize.x, lefyWallSize.y, lefyWallSize.z, GRAY);
        DrawCubeWires(leftWallPos, lefyWallSize.x, lefyWallSize.y, lefyWallSize.z, DARKGRAY);

        // Draw top wall
        DrawCube(topWallPos, topWallSize.x, topWallSize.y, topWallSize.z, GRAY);
        DrawCubeWires(topWallPos, topWallSize.x, topWallSize.y, topWallSize.z, DARKGRAY);


        // Draw player
        DrawSphere(playerPosition, playerRadius, playerColor);

        DrawGrid(20, 1.0f);        // Draw a grid

        EndMode3D();

        DrawText("Move player with cursors to collide", 220, 40, 20, GRAY);

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
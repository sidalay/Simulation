#include "raylib.h"
#include <iostream>
#include <random>

int main(void)
{
    // Initialization
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(144);

    int height{10};
    int width{10};
    int moveSpeed{5};
    float deltaTime{};
    float runningTime{};
    float updateTime{5.f};

    std::random_device seed;
    std::mt19937_64 rand{seed()};

    Rectangle sOne{290, 290, 10, 10};
    Rectangle sTwo{310, 310, 10, 10};

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        std::uniform_int_distribution<int> sOneId(0, 3);
        std::uniform_int_distribution<int> sTwoId(0, 3);

        runningTime += 0.1;

        if (runningTime >= updateTime) {
            switch (sOneId(rand)) {
                case 0:
                    sOne.x -= moveSpeed;
                    break;
                case 1:
                    sOne.x += moveSpeed;
                    break;
                case 2:
                    sOne.y -= moveSpeed;
                    break;
                case 3:
                    sOne.y += moveSpeed;
                    break;
            }
            switch (sTwoId(rand)) {
                case 0:
                    sTwo.x -= moveSpeed;
                    break;
                case 1:
                    sTwo.x += moveSpeed;
                    break;
                case 2:
                    sTwo.y -= moveSpeed;
                    break;
                case 3:
                    sTwo.y += moveSpeed;
                    break;
            }
            runningTime = 0;
        }

        if (sOne.x < 0) {
            sOne.x = 0;
        }
        if (sOne.y < 0) {
            sOne.y = 0;
        }
        if (sOne.x > screenWidth - width) {
            sOne.x = screenWidth - width;
        }
        if (sOne.y > screenHeight - height) {
            sOne.y = screenHeight - height;
        }
        
        if (sTwo.x < 0) {
            sTwo.x = 0;
        }
        if (sTwo.y < 0) {
            sTwo.y = 0;
        }
        if (sTwo.x > screenWidth - width) {
            sTwo.x = screenWidth - width;
        }
        if (sTwo.y > screenHeight - height) {
            sTwo.y = screenHeight - height;
        }
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangle(sOne.x, sOne.y, width, height, GREEN);
            DrawRectangle(sTwo.x, sTwo.y, width, height, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
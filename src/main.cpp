#include <iostream>
#include "soul.hpp"

int main(void)
{
  // Initialization
  Vector2i window{600, 600};

  InitWindow(window.x, window.y, "Simulation");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  std::random_device seed;
  std::mt19937_64 rand{seed()};

  Soul sOne{Rectangle{290, 290, 10, 10}, GREEN, window, rand};
  Soul sTwo{Rectangle{310, 310, 10, 10}, BLUE, window, rand};

  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    sOne.Tick();
    sTwo.Tick();

    // Draw
    BeginDrawing();

    ClearBackground(BLACK);
    sOne.Draw();
    sTwo.Draw();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
#include <iostream>
#include "soul.hpp"

#define debug

int main(void)
{
  // Initialization
  Vector2i window{600, 600};
  Vector2i world{600, 400};

  InitWindow(window.x, window.y, "Simulation");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  std::random_device seed;
  std::mt19937_64 rand{seed()};

  std::array<Soul, 7> souls{
    {
      {1, Rectangle{290, 290, 10, 10}, GREEN, world, rand, souls},
      {2, Rectangle{370, 310, 10, 10}, BLUE, world, rand, souls},
      {3, Rectangle{380, 380, 10, 10}, RED, world, rand, souls},
      {4, Rectangle{250, 50, 10, 10}, ORANGE, world, rand, souls},
      {5, Rectangle{30, 400, 10, 10}, YELLOW, world, rand, souls},
      {6, Rectangle{100, 100, 10, 10}, PURPLE, world, rand, souls},
      {7, Rectangle{500, 150, 10, 10}, WHITE, world, rand, souls}
    }
  };

  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    for (auto& soul:souls) {
      soul.Tick();
    }

    // Draw
    BeginDrawing();

    ClearBackground(BLACK);
    for (auto& soul:souls) {
      soul.Draw();

      #ifdef debug 
      // ---------------------- //
        soul.DrawSpatial(); 
      // ---------------------- //
      #endif
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
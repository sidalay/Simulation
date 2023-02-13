#include <iostream>
#include <array>
#include "soul.hpp"

#define debug

int main(void)
{
  // Initialization
  Vector2i window{600, 600};

  InitWindow(window.x, window.y, "Simulation");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  std::random_device seed;
  std::mt19937_64 rand{seed()};

  std::array<Soul, 7> souls{
    {
      {Rectangle{290, 290, 10, 10}, GREEN, window, rand},
      {Rectangle{370, 310, 10, 10}, BLUE, window, rand},
      {Rectangle{480, 480, 10, 10}, RED, window, rand},
      {Rectangle{250, 50, 10, 10}, ORANGE, window, rand},
      {Rectangle{30, 500, 10, 10}, YELLOW, window, rand},
      {Rectangle{100, 100, 10, 10}, PURPLE, window, rand},
      {Rectangle{500, 150, 10, 10}, WHITE, window, rand}
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
#ifndef SOUL_HPP
#define SOUL_HPP

#include "raylib.h"
#include <bitset>
#include <random>
#include <array>

#define NEUTRAL       0b0000'0000
#define FRIENDLY      0b0000'0001
#define HOSTILE       0b0000'0010
#define CURIOUS       0b0000'0100
#define ENLIGHTENED   0b0000'1000
#define CONFUSED      0b0001'0000
#define ANXIOUS       0b0010'0000
#define FRIGHTENED    0b0100'0000
#define INSANITY      0b1000'0000

class Soul {
public:
  void Tick();
  void Draw();
  [[nodiscard]] const Rectangle GetRectangle() const {return m_body;}
  [[nodiscard]] const Color GetColor() const {return m_color;}
  [[nodiscard]] const int GetId() const {return m_id;}

  // debug
  // ---------------------- //
  void DrawSpatial();
  // ---------------------- //
public:
  Soul(int id,
       Rectangle body, 
       Color color, 
       Vector2i& window, 
       std::mt19937_64& rng,
       std::array<Soul, 7>& souls, 
       std::bitset<8> emotion = NEUTRAL);

private:
  Rectangle       m_body{};
  Color           m_color{};
  int             m_id;
  int             m_speed{10};
  float           m_deltaTime{};
  float           m_updateTime{5.f};
  std::bitset<8>  m_emotions{NEUTRAL};

  Vector2i&                           m_window;
  std::array<Soul, 7>&                m_souls;
  std::mt19937_64&                    m_rng;
  std::uniform_int_distribution<int>  m_direction{0, 4};

  // debug
  // ---------------------- //
  Rectangle       m_spatialCollision{};
  Color           m_spatialColor{WHITE};
  bool            m_decrease{};
  // ---------------------- //
private:
  void UpdatePos();
  void CheckOutOfBounds();
  [[nodiscard]] const bool CheckColliding() const;

  // debug
  // ---------------------- //
  void UpdateSpatialCollision();
  void UpdateSpatialColor();
  // ---------------------- //
};

#endif // SOUL_HPP
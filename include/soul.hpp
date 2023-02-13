#ifndef SOUL_HPP
#define SOUL_HPP

#include "raylib.h"
#include <bitset>
#include <random>

#define NEUTRAL       0b0000'0000
#define HAPPY         0b0000'0001
#define SAD           0b0000'0010
#define ANGRY         0b0000'0100
#define LOVE          0b0000'1000
#define CONFUSED      0b0001'0000
#define ENLIGHTENED   0b0010'0000
#define ANXIOUS       0b0100'0000
#define APATHETIC     0b1000'0000

class Soul {
public:
  void Tick();
  void Draw();
  [[nodiscard]] const Rectangle GetPos() const {return m_body;}
  [[nodiscard]] const Color GetColor() const {return m_color;}
public:
  Soul(Rectangle body, 
       Color color, 
       Vector2i& window, 
       std::mt19937_64& rng, 
       std::bitset<8> emotion = NEUTRAL);

private:
  Rectangle       m_body{};
  Color           m_color{};
  int             m_speed{10};
  float           m_deltaTime{};
  float           m_updateTime{5.f};
  std::bitset<8>  m_emotions{NEUTRAL};
  Vector2i&       m_window;

  std::mt19937_64&                    m_rng;
  std::uniform_int_distribution<int>  m_direction{0, 3};
private:
  void UpdatePos();
  void CheckOutOfBounds();
  [[nodiscard]] const bool Colliding() const;
};

#endif // SOUL_HPP
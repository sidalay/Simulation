#include "soul.hpp"

Soul::Soul(Rectangle body, Color color, Vector2i& window, std::mt19937_64& rng, std::bitset<8> emotion) 
  : m_body{body}, m_color{color}, m_emotions{emotion}, m_window{window}, m_rng{rng} {
}

void Soul::Tick() {
  m_deltaTime += 0.1f;

  if (m_deltaTime >= m_updateTime) {
    UpdatePos();
    m_deltaTime = 0.f;
  }
}

void Soul::UpdatePos() {
  switch (m_direction(m_rng)) {
    case 0:
      m_body.x -= m_speed;
      break;
    case 1:
      m_body.x += m_speed;
      break;
    case 2:
      m_body.y -= m_speed;
      break;
    case 3:
      m_body.y += m_speed;
      break;
  }
  CheckOutOfBounds();
}

void Soul::CheckOutOfBounds() {
  if (m_body.x < 0) {
    m_body.x = 0;
  } else if (m_body.x > m_window.x - m_body.width) {
    m_body.x = m_window.x - m_body.width;
  }

  if (m_body.y < 0) {
    m_body.y = 0;
  } else if (m_body.y > m_window.y - m_body.height) {
    m_body.y = m_window.y - m_body.height;
  }
}

void Soul::Draw() {
  DrawRectangle(m_body.x, m_body.y, m_body.width, m_body.height, m_color);
}
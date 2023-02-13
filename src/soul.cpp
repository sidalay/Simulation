#include "soul.hpp"

Soul::Soul(Rectangle body, Color color, Vector2i& window, std::mt19937_64& rng, std::bitset<8> emotion) 
  : m_body{body}, m_color{color}, m_emotions{emotion}, m_window{window}, m_rng{rng} {
}

void Soul::Tick() {
  m_deltaTime += 0.1f;

  if (m_deltaTime >= m_updateTime) {
    UpdatePos();
    UpdateSpatialCollision();
    m_deltaTime = 0.f;
  }
  UpdateSpatialColor();
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

void Soul::UpdateSpatialCollision() {
  m_spatialCollision.width = m_body.width * 3;
  m_spatialCollision.height = m_body.height * 3;
  m_spatialCollision.x = m_body.x - m_spatialCollision.width/3;
  m_spatialCollision.y = m_body.y - m_spatialCollision.height/3;
}

void Soul::Draw() {
  DrawRectangle(
    m_body.x, 
    m_body.y, 
    m_body.width, 
    m_body.height, 
    m_color);
}


// debug 
// ------------------------------------------------------------------------ //
void Soul::UpdateSpatialColor() {
  if (m_spatialColor.a >= 255) {
    decrease = true;
  } else if  (m_spatialColor.a <= 0) {
    decrease = false;
  }

  if (decrease) {
    m_spatialColor.a -= 1;
  } else {
    m_spatialColor.a += 1;
  }
}

void Soul::DrawSpatial() {
  DrawRectangleLines(
    m_spatialCollision.x, 
    m_spatialCollision.y, 
    m_spatialCollision.width, 
    m_spatialCollision.height, 
    m_spatialColor);
  DrawRectangleLines(
    m_body.x, 
    m_body.y, 
    m_body.width, 
    m_body.height, 
    m_spatialColor);
}
// ------------------------------------------------------------------------ //
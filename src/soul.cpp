#include "soul.hpp"

Soul::Soul(
  int id, 
  Rectangle body, 
  Color color, 
  Vector2i& window, 
  std::mt19937_64& rng,
  std::array<Soul, 7>& souls, 
  std::bitset<8> emotion) 
  : m_body{body}, 
    m_color{color}, 
    m_id{id}, 
    m_emotions{emotion}, 
    m_window{window}, 
    m_souls{souls},
    m_rng{rng} {
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
    case 0: {
      m_body.x -= m_speed;
      if (CheckColliding()) {
        m_body.x += m_speed;
      }
      break;
    }
    case 1:
      m_body.x += m_speed;
      if (CheckColliding()) {
        m_body.x -= m_speed;
      }
      break;
    case 2:
      m_body.y -= m_speed;
      if (CheckColliding()) {
        m_body.y += m_speed;
      }
      break;
    case 3:
      m_body.y += m_speed;
      if (CheckColliding()) {
        m_body.y -= m_speed;
      }
      break;
    case 4:
      break;
  }
  CheckOutOfBounds();
}

void Soul::UpdateAffinity() {
  
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

const bool Soul::CheckColliding() const {
  for (auto& soul:m_souls) {
    if (m_id != soul.GetId()) {
      if (CheckCollisionRecs(m_body, soul.GetRectangle())) {
        return true;
      }
    }
  }
  return false;
}

// debug 
// ------------------------------------------------------------------------ //
void Soul::UpdateSpatialColor() {
  if (m_spatialColor.a >= 255) {
    m_decrease = true;
  } else if  (m_spatialColor.a <= 0) {
    m_decrease = false;
  }

  if (m_decrease) {
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
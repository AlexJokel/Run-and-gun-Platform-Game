#include "roamingenemy.h"

#include <QDebug>

int RoamingEnemy::Borders::RelativePosition(float point) const {
  if (point - left < 1e-3f) {
    return -1;
  }
  if (right - point < 1e-3f) {
    return 1;
  }
  return 0;
}

RoamingEnemy::RoamingEnemy(class Level* level,
                           b2Vec2 position,
                           Borders borders,
                           float horizontal_speed,
                           ShapeInfo* shape_info)
    : Enemy(level, position, horizontal_speed, shape_info),
      borders_(borders) {}

ObjectType RoamingEnemy::Type() const {
  return ObjectType::kRoamingEnemy;
}

void RoamingEnemy::Move() {
  /// The product is positive --> direction and position are
  /// to the same side --> direction must be changed.
  if (direction_ * borders_.RelativePosition(body_->GetWorldCenter().x) > 0) {
    ChangeDirection();
  }
  Enemy::Move();
}

float RoamingEnemy::GetDesiredSpeed() const {
  if (player_visible_) return 0;
  return kHorizontalSpeed_ * direction_;
}

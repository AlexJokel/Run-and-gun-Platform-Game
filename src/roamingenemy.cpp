#include "roamingenemy.h"

#include <QDebug>

RoamingEnemy::RoamingEnemy(class Level* level,
                           b2Vec2 position,
                           float left_border, float right_border,
                           float horizontal_speed,
                           ShapeInfo* shape_info)
    : Enemy(level, position, horizontal_speed, shape_info),
      left_border_(left_border),
      right_border_(right_border) {}

void RoamingEnemy::Move() {
  b2Vec2 impulse(GetDesiredSpeed() - body_->GetLinearVelocity().x, 0);
  impulse *= body_->GetMass();
  body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

float RoamingEnemy::GetDesiredSpeed() {
  if (player_visible_) return 0;
  if ((body_->GetWorldCenter().x - left_border_ < 1e-3f) ||
      (right_border_ - body_->GetWorldCenter().x < 1e-3f)) {
    ChangeDirection();
  }
  return kHorizontalSpeed * direction_;
}

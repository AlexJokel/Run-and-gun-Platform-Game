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
  b2Vec2 impulse(kHorizontalSpeed, 0);
  auto current_speed = body_->GetLinearVelocity().LengthSquared(); /// Squared!
  impulse *= body_->GetMass();

  bool direction_changed = ChangeDirection();

  /// Exit if no need to apply impulse
  /// i.e. when speed is not zero and
  /// direction has not changed
  if (!direction_changed && (current_speed > 1e-6f)) {
    return;
  }

  if (direction_changed) {
    impulse *= 2;
    if (direction_ == Direction::kLeft) impulse *= -1;
  }

  body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

bool RoamingEnemy::ChangeDirection() {
  bool changed = false;

  /// If to the left from the left border
  if (body_->GetWorldCenter().x - left_border_ < 0) {
    direction_ = Direction::kRight;
    changed = true;
  }
  if (right_border_ - body_->GetWorldCenter().x < 0) {
    direction_ = Direction::kLeft;
    changed = true;
  }

  return changed;
}

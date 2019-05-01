#include "staticenemy.h"

StaticEnemy::StaticEnemy(class Level* level,
                         b2Vec2 position,
                         ShapeInfo* shape_info)
    : Enemy(level, position, 0, ObjectType::kStaticEnemy, shape_info) {
  /// Init direction change timer
  QObject::connect(direction_change_timer_, &QTimer::timeout,
                   this, &StaticEnemy::ChangeDirection);
  direction_change_timer_->start(kDirectionChangeInterval_);
}

void StaticEnemy::Move() {
  if (player_visible_) {
    direction_change_timer_->stop();
  } else {
    if (!direction_change_timer_->isActive()) {
      direction_change_timer_->start();
    }
  }
  Enemy::Move();
}

float StaticEnemy::GetDesiredSpeed() const {
  return 0;
}

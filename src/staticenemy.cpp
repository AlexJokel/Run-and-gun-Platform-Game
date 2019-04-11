#include "staticenemy.h"

StaticEnemy::StaticEnemy(class Level* level,
                         b2Vec2 position,
                         ShapeInfo* shape_info)
    : Enemy(level, position, 0, shape_info) {
  /// Init direction change timer
  QObject::connect(direction_change_timer_, &QTimer::timeout,
                   this, &StaticEnemy::ChangeDirection);
  direction_change_timer_->start(kDirectionChangeInterval_);
}

void StaticEnemy::Move() {}

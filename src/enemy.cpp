#include "enemy.h"

#include "level.h"

Enemy::Enemy(class Level* level,
             b2Vec2 position,
             float horizontal_speed,
             ShapeInfo* shape_info)
    : Creature(level, position, horizontal_speed, shape_info) {
  /// Set enemy collision mask
  b2Filter enemy_filter;
  enemy_filter.categoryBits = CollisionMask::kEnemy;
  enemy_filter.maskBits ^= CollisionMask::kEnemy;
  body_->GetFixtureList()->SetFilterData(enemy_filter);

  /// Add color
  setBrush(Qt::red);
  setPen(Qt::NoPen);
}

ObjectType Enemy::Type() const {
  return ObjectType::kEnemy;
}

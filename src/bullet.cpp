#include "bullet.h"

#include "level.h"

Bullet::Bullet(class Level* level,
               float x, float y,
               ShapeInfo* shape_info)
    : Object(level, {x, y, shape_info, BodyType::kDynamic}) {
  /// Set bullet collision mask
  b2Filter bullet_filter;
  bullet_filter.categoryBits = CollisionMask::kBullet;
  bullet_filter.maskBits ^= CollisionMask::kEnemy |
                            CollisionMask::kBullet |
                            CollisionMask::kArrow;
  body_->GetFixtureList()->SetFilterData(bullet_filter);

  body_->SetBullet(true);

  body_->SetGravityScale(0);

  /// Add color
  setBrush(Qt::black);
  setPen(Qt::NoPen);
}

ObjectType Bullet::Type() const {
  return ObjectType::kBullet;
}

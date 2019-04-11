#include "bullet.h"

#include "level.h"

Bullet::Bullet(class Level* level,
               b2Vec2 position,
               ShapeInfo* shape_info)
    : Object(level, {position, shape_info, BodyType::kDynamic}) {
  /// Set bullet collision mask
  b2Filter bullet_filter;
  bullet_filter.categoryBits = CollisionMask::kBullet;
  bullet_filter.maskBits ^= CollisionMask::kEnemy |
                            CollisionMask::kBullet |
                            CollisionMask::kArrow;
  body_->GetFixtureList()->SetFilterData(bullet_filter);

  body_->SetBullet(true);

  body_->SetGravityScale(0);

  body_->ApplyLinearImpulse({kHorizontalSpeed_ * body_->GetMass(), 0},
                            body_->GetWorldCenter(), true);

  /// Add color
  setBrush(Qt::black);
  setPen(Qt::NoPen);
}

ObjectType Bullet::Type() const {
  return ObjectType::kBullet;
}

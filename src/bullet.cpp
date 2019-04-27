#include "bullet.h"

#include "level.h"

Bullet::Bullet(class Level* level,
               b2Vec2 position,
               float direction,
               ShapeInfo* shape_info)
    : Object(level,
             {position, shape_info, BodyType::kDynamic},
             ObjectType::kBullet) {
  /// Set bullet collision mask
  b2Filter bullet_filter;
  bullet_filter.categoryBits = CollisionMask::kBullet;
  bullet_filter.maskBits ^= CollisionMask::kEnemy |
                            CollisionMask::kBullet |
                            CollisionMask::kArrow;
  body_->GetFixtureList()->SetFilterData(bullet_filter);

  body_->SetBullet(true);

  body_->SetGravityScale(0);

  body_->ApplyLinearImpulse(
      {direction * kHorizontalSpeed_ * body_->GetMass(), 0},
      body_->GetWorldCenter(), true);

  /// Set pixmap
  SetPixmap(":/images/images/bullet.jpg", Qt::IgnoreAspectRatio);
  if (direction < 0) {
      ReflectPixmap();
  }
}

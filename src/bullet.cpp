#include "bullet.h"

#include "level.h"

Bullet::Bullet(class Level* level,
               b2Vec2 position,
               b2Vec2 direction,
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

  b2Vec2 impulse = direction;
  impulse *= kSpeed_ / impulse.Length();
  impulse *= body_->GetMass();
  body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);

  body_->SetFixedRotation(false);
  body_->SetTransform(body_->GetWorldCenter(),
                      atan(impulse.y / impulse.x));

  /// Set pixmap
  SetPixmap(":/images/images/bullet.jpg", Qt::IgnoreAspectRatio);
  if (direction.x < 0) {
      ReflectPixmap();
  }
  Draw();
}

void Bullet::Collide(ObjectType, const b2Contact*) {
  Level()->RemoveObject(this);
}

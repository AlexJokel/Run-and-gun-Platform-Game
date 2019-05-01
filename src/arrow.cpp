#include "arrow.h"
#include "level.h"

#include "level.h"

Arrow::Arrow(class Level* scene,
             b2Vec2 position,
             ShapeInfo* shape_info)
    : Object(scene,
             {position, shape_info, BodyType::kDynamic},
             ObjectType::kArrow) {
  ///Enable rotation
  body_->SetFixedRotation(false);

  /// Set starting velocity
  b2Vec2 velocity = Level()->MousePosition() - position;
  velocity *= kSpeed / velocity.Length(); /// Scale to desired length
  body_->SetLinearVelocity(velocity);

  /// Set angle
  SetAngle(velocity);
  Draw();

  /// Set pixmap
  SetPixmap(":/images/images/arrow2.png", Qt::IgnoreAspectRatio);
  if (velocity.x < 0) {
    ReflectPixmap();
  }

  /// Disable arrow-arrow & arrow-player collision
  b2Filter arrow_filter;
  arrow_filter.categoryBits = CollisionMask::kArrow;
  arrow_filter.maskBits ^= CollisionMask::kArrow | CollisionMask::kPlayer;
  body_->GetFixtureList()->SetFilterData(arrow_filter);
}

void Arrow::advance(int phase) {
  SetAngle(body_->GetLinearVelocity());
  Object::advance(phase);
}

void Arrow::Collide(ObjectType) {
  Level()->RemoveObject(this);
}

void Arrow::SetAngle(b2Vec2 velocity) {
  float angle = atan(velocity.y / velocity.x);
  body_->SetTransform(body_->GetWorldPoint({0, 0}), angle);
}

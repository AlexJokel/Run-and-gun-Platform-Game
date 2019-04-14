#include "arrow.h"

Arrow::Arrow(class Level* scene,
             b2Vec2 position,
             b2Vec2 mouse_position,
             ShapeInfo* shape_info)
    : Object(scene, {position, shape_info, BodyType::kDynamic}) {
  ///Enable rotation
  body_->SetFixedRotation(false);

  /// Set starting velocity
  b2Vec2 velocity = mouse_position - position; /// Difference in coordinates
  velocity *= kSpeed / velocity.Length(); /// Scale to desired length
  body_->SetLinearVelocity(velocity);

  /// Set angle
  SetAngle(velocity);
  Draw();

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

ObjectType Arrow::Type() const {
  return ObjectType::kArrow;
}

void Arrow::SetAngle(b2Vec2 velocity) {
  float angle = -atan(velocity.y / velocity.x);
  body_->SetTransform(body_->GetWorldPoint({0, 0}), angle);
}

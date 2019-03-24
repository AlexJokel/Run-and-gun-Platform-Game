#include "arrow.h"

Arrow::Arrow(class Scene* scene,
             float x, float y,
             float mouse_x, float mouse_y,
             ShapeInfo* shape_info)
    : Object(scene, BodyInfo{x, y, shape_info, BodyType::kDynamic}) {
  ///Enable rotation
  body_->SetFixedRotation(false);

  /// Set starting velocity
  b2Vec2 velocity(mouse_x - x, mouse_y - y); /// Difference in coordinates
  velocity *= kSpeed / velocity.Length(); /// Scale to desired length
  body_->SetLinearVelocity(velocity);

  /// Set angle
  SetAngle(velocity);

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

void Arrow::SetAngle(b2Vec2 velocity) {
  float angle = -atan(velocity.y / velocity.x);
  body_->SetTransform(body_->GetWorldPoint({0, 0}), angle);
}

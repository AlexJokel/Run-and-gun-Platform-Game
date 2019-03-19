#include "arrow.h"

Arrow::Arrow(class Scene* scene,
             float x, float y,
             float mouse_x, float mouse_y,
             ShapeInfo* shape_info)
    : Object(scene, BodyInfo{x, y, shape_info, BodyType::kDynamic}) {
  ///Enable rotation
  body_.body->SetFixedRotation(false);

  /// Set starting velocity
  b2Vec2 velocity(mouse_x - x, mouse_y - y); /// Difference in coordinates
  velocity *= kSpeed / velocity.Length(); /// Scale to desired length
  body_.body->SetLinearVelocity(velocity);
}

void Arrow::SetOutOfPlayer() {
  out_of_player = true;
}

bool Arrow::IsOutOfPlayer() const {
  return out_of_player;
}

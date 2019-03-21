#include "player.h"

#include <QGraphicsView>
#include <QDebug>

#include "scene.h"

Player::Player(class Scene* scene,
               float x, float y,
               ShapeInfo* shape_init)
    : Creature(scene, BodyInfo{x, y, shape_init, BodyType::kDynamic}, 5),
      kVerticalSpeed_(CalcSpeedForHeight(scene->World(), kJumpHeight)) {
  /// Set player collision mask
  b2Filter player_filter;
  player_filter.categoryBits = CollisionMask::kPlayer;
  player_filter.maskBits ^= CollisionMask::kArrow;
  body_.body->GetFixtureList()->SetFilterData(player_filter);
}

void Player::advance(int phase) {
  Creature::advance(phase);
  Scene()->views().front()->centerOn(this);
}

void Player::Move() {
  b2Vec2 velocity(0, body_.body->GetLinearVelocity().y);
  if (Scene()->KeyPressed(Qt::Key_A)) {
    velocity.x -= kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_D)) {
    velocity.x += kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_Space)) {
    if (qAbs(velocity.y) < 1e-6f) {
      velocity.y -= kVerticalSpeed_;
    }
  }

  body_.body->SetLinearVelocity(velocity);
}

/// Copy-pasted this function
float Player::CalcSpeedForHeight(b2World* world, float height) {
  if ( height <= 0 )
      return 0;

  float t = 1 / 60.0f;
  b2Vec2 stepGravity = t * t * world->GetGravity();

  float a = -0.5f / stepGravity.y;
  float b = 0.5f;
  float c = height;

  float quadraticSolution1 = ( -b - b2Sqrt( b*b - 4*a*c ) ) / (2*a);
  float quadraticSolution2 = ( -b + b2Sqrt( b*b - 4*a*c ) ) / (2*a);

  float v = quadraticSolution1;
  if ( v < 0 )
      v = quadraticSolution2;

  return v * 60.0f;
}

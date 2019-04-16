#include "player.h"

#include <QGraphicsView>
#include <QDebug>

#include "level.h"

Player::Player(class Level* scene,
               b2Vec2 position,
               ShapeInfo* shape_info)
    : Creature(scene, position, 5, shape_info),
      kVerticalSpeed_(CalcSpeedForHeight(scene->World(), kJumpHeight_)) {
  /// Set player collision mask
  b2Filter player_filter;
  player_filter.categoryBits = CollisionMask::kPlayer;
  player_filter.maskBits ^= CollisionMask::kArrow;
  body_->GetFixtureList()->SetFilterData(player_filter);

  /// Set pixmap
  SetPixmap(":/images/images/player.png", Qt::IgnoreAspectRatio);
}

void Player::ScheduleShot(b2Vec2 direction) {
  shot_.scheduled = true;
  shot_.direction = direction;
}

void Player::advance(int phase) {
  Creature::advance(phase);
  Level()->views().front()->centerOn(this);
}

ObjectType Player::Type() const {
  return ObjectType::kPlayer;
}

float Player::GetDesiredSpeed() const {
  float desired_speed = 0;
  if (Level()->KeyPressed(Qt::Key_A)) {
    desired_speed -= kHorizontalSpeed_;
  }
  if (Level()->KeyPressed(Qt::Key_D)) {
    desired_speed += kHorizontalSpeed_;
  }
  return desired_speed;
}

void Player::Move() {
  Creature::Move();
  if (Level()->KeyPressed(Qt::Key_Space)) {
    if (qAbs(body_->GetLinearVelocity().y) < 1e-3f) {
      body_->ApplyLinearImpulse({0, -kVerticalSpeed_ * body_->GetMass()},
                                body_->GetWorldCenter(), true);
    }
  }
}

void Player::Shoot() {
  if (!shot_.scheduled) return;
  shot_.scheduled = false;
  new Arrow(Level(), body_->GetWorldCenter(), shot_.direction);
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

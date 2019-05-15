#include "player.h"

#include <QGraphicsView>
#include <QDebug>

#include "level.h"
#include "soundeffectstorage.h"

Player::Player(class Level* level,
               b2Vec2 position,
               ShapeInfo* shape_info)
    : Creature(level, position, 5, ObjectType::kPlayer,
               {ObjectType::kBullet, ObjectType::kEnemy},
               shape_info),
      kVerticalSpeed_(CalcSpeedForHeight(level->World(), kJumpHeight_)) {
  /// Set player collision mask
  b2Filter player_filter;
  player_filter.categoryBits = CollisionMask::kPlayer;
  player_filter.maskBits ^= CollisionMask::kArrow;
  body_->GetFixtureList()->SetFilterData(player_filter);

  /// Add fixture to check if grounded
  b2FixtureDef grounded_checker_def;
  grounded_checker_def.filter.maskBits = CollisionMask::kDefault;
  grounded_checker_def.isSensor = true;
  b2EdgeShape grounded_checker_shape;
  auto body_shape = dynamic_cast<b2PolygonShape*>(GetShape());
  grounded_checker_shape.Set(body_shape->GetVertex(3) + b2Vec2(0.01f, 0),
                             body_shape->GetVertex(2) - b2Vec2(0.01f, 0));
  grounded_checker_def.shape = &grounded_checker_shape;
  jump_helper_.grounded_checker_ = body_->CreateFixture(&grounded_checker_def);

  /// Set pixmap
  SetPixmap(":/images/images/elf.png", Qt::IgnoreAspectRatio);

  /// Set initial arrow_count
  arrow_count_ = level->GetProvidedArrowCount();
  QObject::connect(this, &Player::ArrowCountChanged,
                   this, [&]() {
      Level()->UpdateRemainingArrows(arrow_count_);
  });
  emit ArrowCountChanged();
}

void Player::advance(int phase) {
  Creature::advance(phase);
  Level()->views().front()->ensureVisible(this,
      static_cast<int>(Level()->views().front()->width() / 2 -
          transformOriginPoint().x() - 2),
      static_cast<int>(Level()->views().front()->height() / 2 -
          transformOriginPoint().y() - 2));
//  Level()->views().front()->centerOn(this);
}

void Player::Collide(ObjectType type, const b2Contact* contact) {
  Creature::Collide(type, contact);
  if ((contact->GetFixtureA() == jump_helper_.grounded_checker_) ||
      (contact->GetFixtureB() == jump_helper_.grounded_checker_)) {
    jump_helper_.grounded_ ^= true;
    if (jump_helper_.grounded_) jump_helper_.jumped_ = false;
  }
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
  // Change direction if necessary
  auto relative_mouse_x =
      Level()->MousePosition().x - body_->GetWorldCenter().x;
  if (direction_ * relative_mouse_x < 0) {
    ChangeDirection();
  }

  // Handle jumping
  if (jump_helper_.grounded_ && !jump_helper_.jumped_ &&
          Level()->KeyPressed(Qt::Key_Space)) {
    body_->ApplyLinearImpulse({0, -kVerticalSpeed_ * body_->GetMass()},
                              body_->GetWorldCenter(), true);
    jump_helper_.jumped_ = true;
    SoundEffectStorage::Play("Jump");
  }

  Creature::Move();
}

void Player::Shoot() {
  if (!Level()->ButtonReleased(Qt::LeftButton)) return;
  if (arrow_count_ == 0) return;
  --arrow_count_;
  emit ArrowCountChanged();
  new Arrow(Level(), body_->GetWorldCenter());
  SoundEffectStorage::Play("Arrow shot");
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

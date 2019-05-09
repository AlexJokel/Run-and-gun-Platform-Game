#include "enemy.h"
#include "level.h"
#include "bullet.h"

#include <QTimer>
#include <QDebug>

Enemy::Enemy(class Level* level,
             b2Vec2 position,
             float horizontal_speed,
             ObjectType type,
             ShapeInfo* shape_info)
    : Creature(level, position, horizontal_speed, type,
               {ObjectType::kArrow, ObjectType::kPlayer},
               shape_info),
      shot_(new Shot()) {
  /// Set enemy collision mask
  b2Filter enemy_filter;
  enemy_filter.categoryBits = CollisionMask::kEnemy;
  enemy_filter.maskBits ^= CollisionMask::kEnemy;
  body_->GetFixtureList()->SetFilterData(enemy_filter);

  /// Add color
  SetPixmap(":/images/images/enemy.png", Qt::IgnoreAspectRatio);
}

Enemy::NearestObjectCallback::NearestObjectCallback(
    const QVector<ObjectType>& opaque_types)
    : b2RayCastCallback(), opaque_types_(opaque_types) {}

float Enemy::NearestObjectCallback::ReportFixture(b2Fixture* fixture,
                                                  const b2Vec2&,
                                                  const b2Vec2&,
                                                  float fraction) {
  auto found_object = static_cast<Object*>(fixture->GetBody()->GetUserData());
  for (const auto& type : opaque_types_) {
    if (Object::Inherits(found_object->Type(), type)) {
      nearest_object_ = found_object;
      return fraction;
    }
  }
  return -1;
}

Object* Enemy::NearestObjectCallback::GetNearestObject() const {
  return nearest_object_;
}

void Enemy::Shoot() {
  /// Check if the enemy sees the player
  NearestObjectCallback nearest_object_callback({ObjectType::kGround,
                                                 ObjectType::kPlayer});
  b2Vec2 ray_end_point = body_->GetWorldCenter();
  ray_end_point.x += direction_ * Level()->PixelsToMeters(Level()->width());
  Level()->World()->RayCast(&nearest_object_callback,
                            body_->GetWorldCenter(),
                            ray_end_point);

  /// Shoot if necessary
  auto nearest_object = nearest_object_callback.GetNearestObject();
  if (nearest_object == nullptr) return;
  if (nearest_object->Type() ==
      ObjectType::kPlayer) {
    player_visible_ = true;
    if (shot_->TryShooting()) {
      new Bullet(Level(), body_->GetWorldCenter(), direction_);
    }
  } else {
    player_visible_ = false;
  }
}

bool Enemy::Shot::TryShooting() {
  if (!ready_) return false;

  ready_ = false;
  QTimer::singleShot(kCooldownTime, this, &Shot::Ready);
  return true;
}

void Enemy::Shot::Ready() {
  ready_ = true;
}

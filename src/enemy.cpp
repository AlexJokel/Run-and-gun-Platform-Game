#include "enemy.h"

#include "level.h"
#include "bullet.h"

Enemy::Enemy(class Level* level,
             b2Vec2 position,
             float horizontal_speed,
             ShapeInfo* shape_info)
    : Creature(level, position, horizontal_speed, shape_info) {
  /// Set enemy collision mask
  b2Filter enemy_filter;
  enemy_filter.categoryBits = CollisionMask::kEnemy;
  enemy_filter.maskBits ^= CollisionMask::kEnemy;
  body_->GetFixtureList()->SetFilterData(enemy_filter);

  /// Add color
  setBrush(Qt::red);
  setPen(Qt::NoPen);
}

ObjectType Enemy::Type() const {
  return ObjectType::kEnemy;
}

Enemy::NearestObjectCallback::NearestObjectCallback(
    const QSet<ObjectType>& opaque_types)
    : b2RayCastCallback(), opaque_types_(opaque_types) {}

float Enemy::NearestObjectCallback::ReportFixture(b2Fixture* fixture,
                                                  const b2Vec2&,
                                                  const b2Vec2&,
                                                  float fraction) {
  auto found_object = static_cast<Object*>(fixture->GetBody()->GetUserData());
  if (!opaque_types_.contains(found_object->Type())) return -1;
  nearest_object_ = found_object;
  return fraction;
}

Object* Enemy::NearestObjectCallback::GetNearestObject() const {
  return nearest_object_;
}

void Enemy::Shoot() {
  /// Check if the enemy sees the player
  NearestObjectCallback nearest_object_callback({ObjectType::kGround,
                                                 ObjectType::kPlayer});
  b2Vec2 ray_end_point = body_->GetWorldCenter();
  ray_end_point.x -= Level()->PixelsToMeters(Level()->width());
  Level()->World()->RayCast(&nearest_object_callback,
                            body_->GetWorldCenter(),
                            ray_end_point);
  if (nearest_object_callback.GetNearestObject()->Type() ==
      ObjectType::kPlayer) {
    new Bullet(Level(), body_->GetWorldCenter());
  }
}
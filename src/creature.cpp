#include "creature.h"

#include <QGraphicsView>

#include "level.h"

Creature::Creature(class Level* scene,
                   b2Vec2 position,
                   float horizontal_speed,
                   ObjectType type,
                   const QVector<ObjectType>& removers,
                   ShapeInfo* shape_info)
    : Object(scene, {position, shape_info, BodyType::kDynamic}, type),
      kHorizontalSpeed_(horizontal_speed),
      removers_(removers) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Shoot();
  Move();
  Draw();
}

void Creature::Collide(ObjectType collider) {
  RemoveOnCollision(collider, removers_);
}

void Creature::Move() {
  b2Vec2 impulse(GetDesiredSpeed() - body_->GetLinearVelocity().x, 0);
  impulse *= body_->GetMass();
  if (impulse.LengthSquared() < 1e-3f) return;
  body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

void Creature::ChangeDirection() {
  ReflectPixmap();

  direction_ *= -1;
}

void Creature::Shoot() {}

void Creature::RemoveOnCollision(ObjectType collider,
                                 const QVector<ObjectType> &removing_types) {
  for (const auto& remover : removing_types) {
    if (Object::Inherits(collider, remover)) {
      Level()->RemoveObject(this);
    }
  }
}

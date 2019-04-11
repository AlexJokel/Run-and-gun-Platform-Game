#include "creature.h"

#include <QGraphicsView>

#include "level.h"

Creature::Creature(class Level* scene,
                   b2Vec2 position,
                   float horizontal_speed,
                   ShapeInfo* shape_info)
    : Object(scene, {position, shape_info, BodyType::kDynamic}),
      kHorizontalSpeed(horizontal_speed) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Shoot();
  Move();
  Draw();
}

void Creature::ChangeDirection() {
  direction_ *= -1;
}

void Creature::Shoot() {}

#include "creature.h"

#include <QGraphicsView>

#include "level.h"

Creature::Creature(class Level* scene,
                   float x, float y,
                   float horizontal_speed,
                   ShapeInfo* shape_info)
    : Object(scene, {x, y, shape_info, BodyType::kDynamic}),
      kHorizontalSpeed(horizontal_speed) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Move();
  Draw();
}

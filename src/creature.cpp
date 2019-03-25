#include "creature.h"

#include <QGraphicsView>

#include "level.h"

Creature::Creature(class Level* scene,
                   BodyInfo body_info,
                   float horizontal_speed)
    : Object(scene, body_info),
      kHorizontalSpeed(horizontal_speed) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Move();
  Draw();
}

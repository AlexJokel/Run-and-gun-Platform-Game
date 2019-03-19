#include "creature.h"

#include <QGraphicsView>

#include "scene.h"

Creature::Creature(class Scene* scene,
                   BodyInfo body_info,
                   float horizontal_speed,
                   QGraphicsItem* parent)
    : Object(scene, body_info, parent),
      kHorizontalSpeed(horizontal_speed) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Move();
  Draw();
}

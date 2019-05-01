#include "finishpoint.h"

#include "level.h"

FinishPoint::FinishPoint(class Level* level,
                         b2Vec2 position,
                         b2Vec2 size)
    : Ground(level, position, size, ObjectType::kFinishPoint) {}

void FinishPoint::Collide(ObjectType type) {
  if (Object::Inherits(type, ObjectType::kPlayer)) {
    Level()->ScheduleFinish();
  }
}

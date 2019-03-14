#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
public:
  Creature(class Scene*,
           float x, float y,
           ShapeInit*,
           BodyType = BodyType::kDynamic,
           float density = 1,
           QGraphicsItem* parent = nullptr);
};

#endif // CREATURE_H

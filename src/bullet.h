#ifndef BULLET_H
#define BULLET_H

#include "object.h"

class Bullet : public Object {
public:
  Bullet(class Level*,
         float x, float y,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.1f, 0.05f));

  ObjectType Type() const override;
};

#endif // BULLET_H

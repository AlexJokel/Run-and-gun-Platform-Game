#ifndef BULLET_H
#define BULLET_H

#include "object.h"

class Bullet : public Object {
public:
  Bullet(class Level*,
         b2Vec2 position,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.1f, 0.05f));

  ObjectType Type() const override;

protected:
  const float kHorizontalSpeed_ = 10;
};

#endif // BULLET_H

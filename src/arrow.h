#ifndef ARROW_H
#define ARROW_H

#include "object.h"

class Arrow : public Object {
public:
  Arrow(class Level*,
        b2Vec2 position,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.4f, 0.1f));

  void advance(int) override;

  void Collide(ObjectType) override;

protected:
  const float kSpeed = 10;

  void SetAngle(b2Vec2 velocity);
};

#endif // ARROW_H

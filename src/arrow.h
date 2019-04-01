#ifndef ARROW_H
#define ARROW_H

#include "object.h"

class Arrow : public Object {
public:
  Arrow(class Level*,
        float x, float y,
        float mouse_x, float mouse_y,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.4f, 0.1f));

  void advance(int) override;

  ObjectType Type() const override;

protected:
  const float kSpeed = 10;

  void SetAngle(b2Vec2 velocity);
};

#endif // ARROW_H

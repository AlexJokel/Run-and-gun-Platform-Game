#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
public:
  Creature(class Level*,
           b2Vec2 position,
           float horizontal_speed,
           ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void advance(int) override;

protected:
  const float kHorizontalSpeed;

  virtual void Move() = 0;
  virtual void Shoot();
};

#endif // CREATURE_H

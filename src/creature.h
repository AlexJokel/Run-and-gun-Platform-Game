#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
public:
  Creature(class Scene*,
           float x, float y,
           ShapeInit*,
           float horizontal_speed = 5,
           BodyType = BodyType::kDynamic,
           float density = 1,
           QGraphicsItem* parent = nullptr);

  void advance(int) override;

protected:
  const float kHorizontalSpeed;

  virtual void Move() = 0;
  virtual void Draw();
};

#endif // CREATURE_H

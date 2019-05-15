#ifndef BULLET_H
#define BULLET_H

#include "object.h"

class Bullet : public Object {
public:
  Bullet(class Level*,
         b2Vec2 position,
         b2Vec2 direction,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.1f, 0.05f));

  void Collide(ObjectType, const b2Contact*) override;

protected:
  const float kSpeed_ = 10;
};

#endif // BULLET_H

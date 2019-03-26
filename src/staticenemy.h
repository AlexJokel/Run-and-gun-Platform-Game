#ifndef STATICENEMY_H
#define STATICENEMY_H

#include "enemy.h"

class StaticEnemy : public Enemy {
public:
  StaticEnemy(class Level*,
              float x, float y,
              ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

protected:
  void Move() override;
};

#endif // STATICENEMY_H

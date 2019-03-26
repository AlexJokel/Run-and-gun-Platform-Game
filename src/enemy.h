#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

class Enemy : public Creature {
public:
  Enemy(class Level*,
        float x, float y,
        float horizontal_speed,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));
};

#endif // ENEMY_H

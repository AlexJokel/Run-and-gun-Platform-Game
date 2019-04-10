#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

class Enemy : public Creature {
public:
  Enemy(class Level*,
        b2Vec2 position,
        float horizontal_speed,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  ObjectType Type() const override;
};

#endif // ENEMY_H
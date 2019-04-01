#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "creature.h"

class Player : public Creature {
public:
  Player(class Level*,
         float x, float y,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));
  ~Player() override;

  void advance(int) override;

  ObjectType Type() const override;

protected:
  const float kJumpHeight = 3;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  void Move() override;
};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "creature.h"

class Player : public Creature {
public:
  Player(class Level*,
         b2Vec2 position,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void ScheduleShot(b2Vec2 direction);
  void advance(int) override;

  ObjectType Type() const override;

protected:
  const float kJumpHeight = 3;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  struct Shot {
    bool scheduled = false;
    b2Vec2 direction;
  };
  Shot shot_;

  void Move() override;
  void Shoot() override;
};

#endif // PLAYER_H

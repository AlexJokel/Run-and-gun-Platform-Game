#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "creature.h"
#include "scene.h"

class Player : public Creature {
public:
  Player(b2World*, QGraphicsItem* = nullptr);

  void advance(int) override;

  Scene* Scene() const;

  ~Player() override;

private:
  constexpr static float kJumpHeight = 3;
  constexpr static float kHorizontalSpeed = 5;
  const float kVerticalSpeed_;
  static float CalcSpeedForHeight(b2World*, float);

  void Draw();
  void Move();
};

#endif // PLAYER_H

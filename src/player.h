#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>
#include <QMouseEvent>

#include <Box2D/Box2D.h>

#include "creature.h"

class Player : public Creature {
public:
  Player(class Level*,
         b2Vec2 position,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void advance(int) override;

  struct Controls {
      Qt::Key left = Qt::Key_A;
      Qt::Key right = Qt::Key_D;
      Qt::Key jump = Qt::Key_Space;
      Qt::MouseButton shoot = Qt::LeftButton;
      Qt::MouseButton exit = Qt::RightButton;
  };
  static Controls controls_;
  ObjectType Type() const override;

protected:
  const float kJumpHeight_ = 3;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  float GetDesiredSpeed() const override;
  void Move() override;
  void Shoot() override;
};

#endif // PLAYER_H

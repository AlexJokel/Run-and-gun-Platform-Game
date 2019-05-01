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

  static QMap<QString, Qt::Key> controls_map_;
protected:
  const float kJumpHeight_ = 3;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  float GetDesiredSpeed() const override;
  void Move() override;
  void Shoot() override;
};

#endif // PLAYER_H

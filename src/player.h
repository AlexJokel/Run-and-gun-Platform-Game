#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "creature.h"

class Player : public Creature {
  Q_OBJECT
public:
  Player(class Level*,
         b2Vec2 position,
         ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void advance(int) override;

protected:
  const float kJumpHeight_ = 3;
  const float kVerticalSpeed_ = 10;
  qint32 arrow_count_;

  static float CalcSpeedForHeight(b2World*, float);

  float GetDesiredSpeed() const override;
  void Move() override;
  void Shoot() override;
protected: signals:
  void ArrowCountChanged() const;
};

#endif // PLAYER_H

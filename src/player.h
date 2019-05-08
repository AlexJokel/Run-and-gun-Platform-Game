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

  void Collide(ObjectType, const b2Contact*) override;

protected:
  // if exactly 3 then the player collides with the exact corner
  // of a ground at a height of 2 (seems like Box2D bug).
  const float kJumpHeight_ = 3.001f;
  const float kVerticalSpeed_;
  static float CalcSpeedForHeight(b2World*, float);

  qint32 arrow_count_;

  struct JumpHelper {
    b2Fixture* grounded_checker_ = nullptr;
    bool grounded_ = false;
    bool jumped_ = false;
  };
  JumpHelper jump_helper_;

  float GetDesiredSpeed() const override;
  void Move() override;
  void Shoot() override;
protected: signals:
  void ArrowCountChanged() const;
};

#endif // PLAYER_H

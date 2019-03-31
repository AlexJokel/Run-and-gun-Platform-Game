#ifndef ROAMINGENEMY_H
#define ROAMINGENEMY_H

#include "enemy.h"

class RoamingEnemy : public Enemy {
public:
  RoamingEnemy(class Level*,
               float x, float y,
               float left_border, float right_border,
               float horizontal_speed = 2,
               ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

protected:
  float left_border_;
  float right_border_;

  enum class Direction {
    kLeft,
    kRight,
  };
  bool ChangeDirection();
  b2Vec2 GetDesiredSpeed();
  Direction direction_ = Direction::kLeft;

  void Move() override;
};

#endif // ROAMINGENEMY_H

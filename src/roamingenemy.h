#ifndef ROAMINGENEMY_H
#define ROAMINGENEMY_H

#include "enemy.h"

class RoamingEnemy : public Enemy {
public:
  RoamingEnemy(class Level*,
               b2Vec2 position,
               float left_border, float right_border,
               float horizontal_speed = 2,
               ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

protected:
  float left_border_;
  float right_border_;

  void Move() override;

  /// Calculate necessary speed in the current state.
  /// 0 if the player is visible.
  /// kHorizontalSpeed in appropriate direction otherwise.
  float GetDesiredSpeed();
};

#endif // ROAMINGENEMY_H

#ifndef ROAMINGENEMY_H
#define ROAMINGENEMY_H

#include "enemy.h"

class RoamingEnemy : public Enemy {
public:
  struct Borders {
    float left;
    float right;

    /// Check position of point relative to borders. Returns:
    ///   1 if the point is to the right;
    ///   0 if inside the borders;
    ///   -1 if to the left.
    int RelativePosition(float point) const;
  };

  RoamingEnemy(class Level*,
               b2Vec2 position,
               Borders borders,
               float horizontal_speed = 2,
               ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  ObjectType Type() const override;

protected:
  Borders borders_;

  void Move() override;
  float GetDesiredSpeed() const override;
};

#endif // ROAMINGENEMY_H

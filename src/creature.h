#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
  Q_OBJECT
public:
  Creature(class Level*,
           b2Vec2 position,
           float horizontal_speed,
           ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void advance(int) override;

public slots:
  /// Invert the direction
  void ChangeDirection();

protected:
  const float kHorizontalSpeed;

  virtual void Move() = 0;
  virtual void Shoot();

  /// Direction by x-axis coefficient.
  /// By default everybody "looks" to the right
  int direction_ = 1;
};

#endif // CREATURE_H

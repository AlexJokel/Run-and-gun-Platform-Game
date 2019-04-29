#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
  Q_OBJECT
public:
  Creature(class Level*,
           b2Vec2 position,
           float horizontal_speed,
           ObjectType = ObjectType::kCreature,
           const QVector<ObjectType>& removers = {},
           ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  void advance(int) override;

  void Collide(ObjectType) override;

public slots:
  /// Invert the direction
  void ChangeDirection();

protected:
  const float kHorizontalSpeed_;

  /// Handles horizontal movement.
  /// Uses impulses.
  virtual void Move();

  virtual void Shoot();

  /// Calculate necessary horizontal speed.
  virtual float GetDesiredSpeed() const = 0;

  /// Direction by x-axis coefficient.
  /// By default everybody "looks" to the right
  int direction_ = 1;

  const QVector<ObjectType> removers_;
  void RemoveOnCollision(ObjectType collider,
                         const QVector<ObjectType>& removing_types);
};

#endif // CREATURE_H

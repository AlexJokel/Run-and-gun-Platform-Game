#ifndef STATICENEMY_H
#define STATICENEMY_H

#include "enemy.h"

#include <QTimer>

class StaticEnemy : public Enemy {
  Q_OBJECT
public:
  StaticEnemy(class Level*,
              b2Vec2 position,
              ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));
  ~StaticEnemy() override;

protected:
  void Move() override;
  float GetDesiredSpeed() const override;

  QTimer* direction_change_timer_ = new QTimer();
  const int kDirectionChangeInterval_ = 5000; /// In msec
};

#endif // STATICENEMY_H

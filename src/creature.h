#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
public:
  Creature(class Level*,
           BodyInfo,
           float horizontal_speed);

  void advance(int) override;

protected:
  const float kHorizontalSpeed;

  virtual void Move() = 0;
};

#endif // CREATURE_H

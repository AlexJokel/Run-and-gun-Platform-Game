#ifndef GROUND_H
#define GROUND_H

#include "object.h"

class Ground : public Object {
public:
  /// x, y --- top left corner Box2D coordinates
  Ground(class Level*,
         float x, float y,
         float width, float height);

  ObjectType Type() const override;
};

#endif // GROUND_H

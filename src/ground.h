#ifndef GROUND_H
#define GROUND_H

#include "object.h"

class Ground : public Object {
public:
  /// x, y --- top left corner Box2D coordinates
  Ground(class Level*,
         b2Vec2 position,
         b2Vec2 size);
};

#endif // GROUND_H

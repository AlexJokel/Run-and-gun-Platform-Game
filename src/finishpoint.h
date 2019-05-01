#ifndef FINISHPOINT_H
#define FINISHPOINT_H

#include "ground.h"

class FinishPoint : public Ground {
public:
  /// x, y --- top left corner Box2D coordinates
  FinishPoint(class Level*,
              b2Vec2 position,
              b2Vec2 size);

  void Collide(ObjectType) override;
};

#endif // FINISHPOINT_H

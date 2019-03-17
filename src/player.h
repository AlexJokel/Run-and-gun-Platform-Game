#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "creature.h"
#include "scene.h"

class Player : public Creature {
public:
  Player(class Scene*,
         float x, float y,
         ShapeInfo* = PassShapeInit(ShapeType::kPolygon, 0.5f, 0.5f),
         QGraphicsItem* = nullptr);

protected:
  constexpr static float kJumpHeight = 3;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  void Move() override;
};

#endif // PLAYER_H

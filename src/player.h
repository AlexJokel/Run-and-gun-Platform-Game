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
         ShapeInit* = PassShapeInit(ShapeType::kPolygon, 0.5f, 0.5f),
         float density = 1,
         QGraphicsItem* = nullptr);

  void advance(int) override;

protected:
  constexpr static float kJumpHeight = 3;
  constexpr static float kHorizontalSpeed = 5;
  const float kVerticalSpeed_ = 10;
  static float CalcSpeedForHeight(b2World*, float);

  void Draw();
  void Move();
};

#endif // PLAYER_H

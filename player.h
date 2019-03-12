#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include <Box2D/Box2D.h>

#include "scene.h"

class Player : public QGraphicsRectItem
{
public:
  Player(b2World*, QGraphicsItem* = nullptr);

  void advance(int) override;

  Scene* Scene() const;

  ~Player() override;

private:
  b2Body* body_;
  b2BodyDef* body_def_;
  b2FixtureDef* body_fixture_def_;
  b2PolygonShape* body_shape_;

  constexpr static float32 kHorizontalSpeed = 5;

  void Draw();
  void Move();
};

#endif // PLAYER_H

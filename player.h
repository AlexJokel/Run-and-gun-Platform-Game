#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

#include "scene.h"

class Player : public QGraphicsRectItem
{
public:
  Player(QGraphicsItem* = nullptr);

  void advance(int) override;

  Scene* Scene() const;

private:
  void move();
};

#endif // PLAYER_H

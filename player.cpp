#include "player.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>

Player::Player(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
  setRect(0, 0, 100, 100);
}

void Player::advance(int phase)
{
  if (phase == 0) return;
  move();
  scene()->views().front()->centerOn(this);
}

Scene* Player::Scene() const {
  return dynamic_cast<class Scene*>(scene());
}

void Player::move()
{
  const qreal kSpeed = 250;
  const qreal kShiftPerFrame = kSpeed / 60;
  if (Scene()->KeyPressed(Qt::Key_W)) {
    moveBy(0, - kShiftPerFrame);
  }
  if (Scene()->KeyPressed(Qt::Key_S)) {
    moveBy(0, kShiftPerFrame);
  }
  if (Scene()->KeyPressed(Qt::Key_A)) {
    moveBy(- kShiftPerFrame, 0);
  }
  if (Scene()->KeyPressed(Qt::Key_D)) {
    moveBy(kShiftPerFrame, 0);
  }
}

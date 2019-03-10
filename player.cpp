#include "player.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>

Player::Player(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
  setRect(0, 0, 100, 100);
}

void Player::keyPressEvent(QKeyEvent* event)
{
  keys[event->key()] = true;
}

void Player::keyReleaseEvent(QKeyEvent* event)
{
  keys[event->key()] = false;
}

void Player::advance(int phase)
{
  if (phase == 0) return;
  move();
  scene()->views().front()->centerOn(this);
}

void Player::move()
{
  const qreal kSpeed = 250;
  const qreal kShiftPerFrame = kSpeed / 60;
  if (keys[Qt::Key_W]) {
    setPos(x(), y() - kShiftPerFrame);
  }
  if (keys[Qt::Key_S]) {
    setPos(x(), y() + kShiftPerFrame);
  }
  if (keys[Qt::Key_A]) {
    setPos(x() - kShiftPerFrame, y());
  }
  if (keys[Qt::Key_D]) {
    setPos(x() + kShiftPerFrame, y());
  }
}

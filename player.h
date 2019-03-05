#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMap>

class Player : public QGraphicsRectItem
{
public:
  Player(QGraphicsItem* = nullptr);

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  void advance(int) override;

private:
  QMap<int, bool> keys;

  void move();
};

#endif // PLAYER_H

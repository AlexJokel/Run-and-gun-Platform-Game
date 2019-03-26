#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Game;

class Scene : public QGraphicsScene {
public:
  Scene(Game*, qreal width, qreal height);

  Game* Game() const;

public slots:
  void Exit();

protected:
  class Game* game_;
};

#endif // SCENE_H

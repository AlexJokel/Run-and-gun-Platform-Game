#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Game;

class Scene : public QGraphicsScene {
public:
  Scene(qreal width, qreal height);

  Game* Game() const;
protected:
  class Game* game_;
};

#endif // SCENE_H

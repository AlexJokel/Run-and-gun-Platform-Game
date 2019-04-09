#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Game;

class Scene : public QGraphicsScene {
public:
  Scene(Game*, qreal width, qreal height);

  Game* Game() const;

  void keyPressEvent(QKeyEvent*) override;

protected:
  class Game* game_;
};

#endif // SCENE_H

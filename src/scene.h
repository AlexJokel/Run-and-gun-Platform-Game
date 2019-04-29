#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Game;

class Scene : public QGraphicsScene {
  Q_OBJECT
public:
  Scene(Game*, qreal width, qreal height);

  Game* Game() const;

  void keyPressEvent(QKeyEvent*) override;

public slots:
  virtual void Pause();
  virtual void Unpause();

protected:
  class Game* game_;
};

#endif // SCENE_H

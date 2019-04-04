#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QStack>

#include "scene.h"

class Game : public QGraphicsView {
  Q_OBJECT
public:
  Game();

public slots:
  void PushScene(Scene*);
  void PopScene();

protected:
  QStack<Scene*> scenes_;
};

#endif // GAME_H

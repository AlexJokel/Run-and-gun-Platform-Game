#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

#include "scene.h"

class Game : public QGraphicsView {
    Q_OBJECT
public:
  Game();

public slots:
  void Exit();
  void SetScene(Scene*);

protected:
  Scene* current_scene = nullptr;
};

#endif // GAME_H

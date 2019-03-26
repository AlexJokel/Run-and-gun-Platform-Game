#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

#include "scene.h"

class Game : public QGraphicsView {
public:
  Game();

  void SetScene(Scene*);

protected:
  Scene* current_scene = nullptr;
};

#endif // GAME_H

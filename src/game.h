#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QStack>

#include "scene.h"

class Game : public QGraphicsView {
public:
  Game();

  void PushScene(Scene*);
  void PopScene(bool exit_on_empty_stack = true);

  /// Deprecated
  void SetScene(Scene*);

public slots:
  /// Deprecated
  void Exit();

protected:
  QStack<Scene*> scenes_;
};

#endif // GAME_H

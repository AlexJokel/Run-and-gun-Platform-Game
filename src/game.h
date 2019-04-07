#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QStack>
#include <QApplication>

#include "scene.h"

class Game : public QGraphicsView {
  Q_OBJECT
public:
  Game(QApplication*);

public slots:
  void PushScene(Scene*);
  void PopScene();

protected:
  QApplication* application_;

  QStack<Scene*> scenes_;

  class ScrollDisabler : public QObject {
  protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
  };
};

#endif // GAME_H

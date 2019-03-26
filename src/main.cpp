#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>
#include <QDebug>

#include <Box2D/Box2D.h>

#include "game.h"
#include "level.h"
#include "player.h"
#include "ground.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  /// Scene & view initialization
  auto game = new Game();

  return a.exec();
}

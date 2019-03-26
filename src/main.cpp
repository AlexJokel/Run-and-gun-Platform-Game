#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>
#include <QDebug>

#include <Box2D/Box2D.h>

#include "level.h"
#include "player.h"
#include "ground.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  /// Scene & view initialization
  auto level = new Level(1920, 1080);
  auto view = new QGraphicsView(level);
  view->setFixedSize(1280, 720);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

  view->show();

  return a.exec();
}

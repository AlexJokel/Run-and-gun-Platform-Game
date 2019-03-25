#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>
#include <QDebug>

#include <Box2D/Box2D.h>

#include "scene.h"
#include "player.h"
#include "ground.h"
#include "contactlistener.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  /// World initialization
  auto world = new b2World(b2Vec2(0, 9.8f));
  world->SetContactListener(new ContactListener());

  /// Scene & view initialization
  auto level = new Level(world, 0, 0, 1920, 1080);
  auto view = new QGraphicsView(level);
  view->setFixedSize(1280, 720);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

  /// Draw dot grid
  for (size_t x = 0; x < level->width(); x += 100) {
    for (size_t y = 0; y < level->height(); y += 100) {
      level->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  return a.exec();
}

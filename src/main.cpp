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

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  /// World initialization
  auto world = new b2World(b2Vec2(0, 9.8f));

  /// Scene & view initialization
  auto scene = new Scene(world, 0, 0, 1920, 1080);
  auto view = new QGraphicsView(scene);
  view->setFixedSize(1280, 720);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  /// Player initialization
  auto player = new Player(scene, 3, 3);

  /// Create floor
  auto floor = new Ground(scene,
                          0,
                          Scene::PixelsToMeters(scene->height()) - 1,
                          Scene::PixelsToMeters(scene->width()),
                          1);

  /// Create walls
  auto left_wall = new Ground(scene,
                              0,
                              0,
                              1,
                              Scene::PixelsToMeters(scene->height()));
  auto right_wall = new Ground(scene,
                               Scene::PixelsToMeters(scene->width()) - 1,
                               0,
                               1,
                               Scene::PixelsToMeters(scene->height()));

  /// Draw dot grid
  for (size_t x = 0; x < scene->width(); x += 100) {
    for (size_t y = 0; y < scene->height(); y += 100) {
      scene->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  return a.exec();
}

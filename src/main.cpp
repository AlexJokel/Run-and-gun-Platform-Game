#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>
#include <QDebug>

#include <Box2D/Box2D.h>

#include "scene.h"
#include "player.h"

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
  auto player = new Player(world);
  scene->addItem(player);

  /// Create floor
  b2BodyDef floor_def;
  floor_def.type = b2_staticBody;
  floor_def.position.Set(0,
                         Scene::PixelsToMeters(scene->height()));
  b2EdgeShape floor_shape;
  floor_shape.Set(b2Vec2(0, 0),
                  b2Vec2(Scene::PixelsToMeters(scene->width()), 0));
  b2Body* floor = world->CreateBody(&floor_def);
  floor->CreateFixture(&floor_shape, 1);

  /// Draw dot grid
  for (size_t x = 0; x < scene->width(); x += 100) {
    for (size_t y = 0; y < scene->height(); y += 100) {
      scene->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  return a.exec();
}
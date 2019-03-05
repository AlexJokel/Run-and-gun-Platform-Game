#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include "player.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  auto scene = new QGraphicsScene();
  auto view = new QGraphicsView(scene);

  view->setFixedSize(1280, 720);

  auto player = new Player();
  scene->addItem(player);

  view->show();

  return a.exec();
}

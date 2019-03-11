#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPoint>

#include <QTimer>

#include "player.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // Scene & view initialization
  auto scene = new QGraphicsScene(0, 0, 1920, 1080);
  auto view = new QGraphicsView(scene);
  view->setFixedSize(1280, 720);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Player initialization
  auto player = new Player();
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();
  scene->addItem(player);

  // Draw dot grid
  for(size_t x = 0; x < scene->width(); x += 100) {
    for (size_t y = 0; y < scene->height(); y += 100) {
      scene->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  // Frame timer initialization & start
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
  frame_timer->start(static_cast<int>(1000 / 60.0));

  return a.exec();
}

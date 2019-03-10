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

  auto scene = new QGraphicsScene(0, 0, 1920, 1080);
  auto view = new QGraphicsView(scene);

//  view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
  view->setFixedSize(1280, 720);

  auto player = new Player();
  scene->addItem(player);

  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  for(size_t x = 0; x < scene->width(); x += 100) {
    for (size_t y = 0; y < scene->height(); y += 100) {
      scene->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
  frame_timer->start(static_cast<int>(1000 / 60.0));

  return a.exec();
}

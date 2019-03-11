#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>

#include <QTimer>

#include "scene.h"
#include "player.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // Scene & view initialization
  auto scene = new Scene(0, 0, 1920, 1080);
  auto view = new QGraphicsView(scene);
  view->setFixedSize(1280, 720);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Player initialization
  auto player = new Player();
  scene->addItem(player);

  // Draw dot grid
  for(size_t x = 0; x < scene->width(); x += 100) {
    for (size_t y = 0; y < scene->height(); y += 100) {
      scene->addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  view->show();

  // Frame timer initialization & start
  const qint32 kFramesPerSecond = 60;
  const qreal kTimeStep = 1 / static_cast<qreal>(kFramesPerSecond);
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
  frame_timer->start(static_cast<int>(1000 * kTimeStep));

  return a.exec();
}

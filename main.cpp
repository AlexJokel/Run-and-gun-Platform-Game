#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QTimer>

#include "player.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  auto scene = new QGraphicsScene(0, 0, 1280, 720);
  auto view = new QGraphicsView(scene);

//  view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
  view->setFixedSize(1280, 720);

  auto player = new Player();
  scene->addItem(player);

  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  view->show();

  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
  frame_timer->start(static_cast<int>(1000 / 60.0));

  return a.exec();
}

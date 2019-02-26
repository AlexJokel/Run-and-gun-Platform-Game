#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  auto scene = new QGraphicsScene();
  auto view = new QGraphicsView(scene);
  view->show();

  return a.exec();
}

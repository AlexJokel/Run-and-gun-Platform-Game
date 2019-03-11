#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene {
public:
  Scene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);

public slots:
  void advance();

private:
};

#endif // SCENE_H

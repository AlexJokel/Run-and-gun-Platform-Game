#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include <QKeyEvent>

#include <QMap>

class Scene : public QGraphicsScene {
public:
  Scene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  bool KeyPressed(qint32 key) const;

public slots:
  void advance();

private:
  QMap<qint32, bool> keys;
};

#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMap>

#include <Box2D/Box2D.h>

#include "player.h"
#include "ground.h"

class Scene : public QGraphicsScene {
public:
  Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
        QObject* parent = nullptr);

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  bool KeyPressed(qint32) const;

  void AddObject(Object*);

  b2World* World() const;

  const qreal kMetersToPixelsRatio_ = 100;
  qreal MetersToPixels(float) const;
  float PixelsToMeters(qreal) const;

public slots:
  void advance();

protected:
  b2World* world_;

  const qint32 kFramesPerSecond_ = 60;
  const qreal kTimeStep_ = 1 / static_cast<qreal>(kFramesPerSecond_);

  QMap<qint32, bool> keys_;

  struct SceneObjects {
    Player* player;
    QList<Ground*> ground;
  };

  SceneObjects objects_;
};

#endif // SCENE_H

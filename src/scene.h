#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMap>

#include <Box2D/Box2D.h>

class Object;

class Scene : public QGraphicsScene {
public:
  Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
        QObject* parent = nullptr);

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  void AddObject(Object*);

  bool KeyPressed(qint32) const;

  b2World* World() const;

  constexpr static qreal kMetersToPixelsRatio_ = 100;
  static qreal MetersToPixels(float);
  static float PixelsToMeters(qreal);

public slots:
  void advance();

protected:
  b2World* world_;

  const qint32 kFramesPerSecond_ = 60;
  const qreal kTimeStep_ = 1 / static_cast<qreal>(kFramesPerSecond_);

  QMap<qint32, bool> keys_;
};

#endif // SCENE_H

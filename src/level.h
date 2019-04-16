#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMap>
#include <QSet>

#include <Box2D/Box2D.h>

#include "scene.h"
#include "player.h"
#include "ground.h"
#include "arrow.h"
#include "enemy.h"

class Level : public Scene {
public:
  Level(class Game*, qreal width, qreal height);
  ~Level() override;

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void mousePressEvent(QGraphicsSceneMouseEvent*) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

  bool KeyPressed(qint32) const;
  b2Vec2 MousePosition() const;
  bool ButtonPressed(Qt::MouseButton) const;
  bool ButtonReleased(Qt::MouseButton) const;

  void RemoveObject(Object*);

  b2World* World() const;

  qreal MetersToPixels(float) const;
  QPointF MetersToPixels(b2Vec2) const;
  float PixelsToMeters(qreal) const;
  b2Vec2 PixelsToMeters(QPointF) const;

public slots:
  void advance();

protected:
  b2World* world_;

  const qreal kMetersToPixelsRatio_ = 100;

  const qint32 kFramesPerSecond_ = 60;
  const qreal kTimeStep_ = 1 / static_cast<qreal>(kFramesPerSecond_);

  struct MouseState {
    b2Vec2 mouse_position;
    QSet<Qt::MouseButton> buttons_pressed;
    QSet<Qt::MouseButton> buttons_released;
    void ClearButtons();
  };
  MouseState mouse_state_;
  QMap<qint32, bool> keys_;

  struct SceneObjects {
    Player* player;
    QList<Ground*> ground;
    QList<Enemy*> enemies;
  };

  SceneObjects objects_;

  QSet<Object*> objects_for_removal;
};

#endif // LEVEL_H

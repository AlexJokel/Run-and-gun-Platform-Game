#include "scene.h"

#include <QTimer>

Scene::Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
             QObject* parent)
    : QGraphicsScene(x, y, width, height, parent), world_(world) {
  // Frame timer initialization & start
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, SIGNAL(timeout()), this, SLOT(advance()));
  frame_timer->start(static_cast<int>(1000 * kTimeStep_));
}

void Scene::advance() {
  world_->Step(static_cast<float32>(kTimeStep_), 6, 2);
  QGraphicsScene::advance();
}

void Scene::keyPressEvent(QKeyEvent *event) {
  keys_[event->key()] = true;
}

void Scene::keyReleaseEvent(QKeyEvent *event) {
  keys_[event->key()] = false;
}

bool Scene::KeyPressed(qint32 key) const {
  return keys_.value(key, false);
}

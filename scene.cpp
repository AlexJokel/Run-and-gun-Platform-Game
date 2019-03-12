#include "scene.h"

#include <QTimer>
#include <QDebug>

Scene::Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
             QObject* parent)
    : QGraphicsScene(x, y, width, height, parent), world_(world) {
  // Frame timer initialization & start
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, &QTimer::timeout, this, &Scene::advance);
  frame_timer->start(static_cast<int>(1000 * kTimeStep_));
}

void Scene::advance() {
  world_->Step(static_cast<float32>(kTimeStep_), 8, 3);
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

qreal Scene::MetersToPixels(float32 meters) {
  return static_cast<qreal>(meters) * kMetersToPixelsRatio_;
}

float32 Scene::PixelsToMeters(qreal pixels) {
  return static_cast<float32>(pixels / kMetersToPixelsRatio_);
}

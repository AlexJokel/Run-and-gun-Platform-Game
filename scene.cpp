#include "scene.h"


Scene::Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
             QObject* parent)
    : QGraphicsScene(x, y, width, height, parent), world_(world) {
}

void Scene::advance() {
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

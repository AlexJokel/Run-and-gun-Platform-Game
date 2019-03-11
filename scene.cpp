#include "scene.h"


Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent) {

}

void Scene::advance() {
  QGraphicsScene::advance();
}

void Scene::keyPressEvent(QKeyEvent *event) {
  keys[event->key()] = true;
}

void Scene::keyReleaseEvent(QKeyEvent *event) {
  keys[event->key()] = false;
}

bool Scene::KeyPressed(qint32 key) const {
  return keys.value(key, false);
}

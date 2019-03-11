#include "scene.h"


Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent) {

}

void Scene::advance() {
  QGraphicsScene::advance();
}

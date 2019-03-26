#include "scene.h"

#include "game.h"

Scene::Scene(qreal width, qreal height)
    : QGraphicsScene(0, 0, width, height, nullptr) {}

Game* Scene::Game() const {
  return game_;
}

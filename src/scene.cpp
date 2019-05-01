#include "scene.h"

#include "game.h"

Scene::Scene(class Game* game, qreal width, qreal height)
    : QGraphicsScene(0, 0, width, height, nullptr),
      game_(game) {}

Game* Scene::Game() const {
  return game_;
}

void Scene::keyPressEvent(QKeyEvent*) {}

void Scene::Pause() {}
void Scene::Unpause() {}

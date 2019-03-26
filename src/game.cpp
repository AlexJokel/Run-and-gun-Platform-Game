#include "game.h"

#include "level.h"

Game::Game() : QGraphicsView() {
  setFixedSize(1280, 720);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  SetScene(new Level(1920, 1080));

  show();
}

void Game::SetScene(Scene* scene) {
  delete current_scene;
  setScene(scene);
}

#include "game.h"
#include "level.h"
#include "button.h"
#include "main_menu.h"

Game::Game() : QGraphicsView() {
  setFixedSize(1280, 720);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  PushScene(new MainMenu(this, 1920, 1080, Qt::lightGray));

  show();
}

void Game::PushScene(Scene* scene) {
  setScene(scene);
  scenes_.push(scene);
}

void Game::PopScene() {
  delete scenes_.top();
  scenes_.pop();
  setScene(scenes_.top());

  if (scenes_.empty()) {
    close();
  }
}

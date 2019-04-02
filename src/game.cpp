#include "game.h"

#include "level.h"

Game::Game() : QGraphicsView() {
  setFixedSize(1280, 720);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  PushScene(new Level(this, 1920, 1080));

  show();
}

void Game::PushScene(Scene* scene) {
  setScene(scene);
  scenes_.push(scene);
}

void Game::PopScene(bool exit_on_empty_stack) {
  delete scenes_.top();
  scenes_.pop();
  setScene(scenes_.top());

  if (exit_on_empty_stack && scenes_.empty()) {
    close();
  }
}

void Game::SetScene(Scene* scene) {
  while (!scenes_.empty()) {
    PopScene(false);
  }
  PushScene(scene);
}

void Game::Exit() {
  close();
}

#include "game.h"
#include "level.h"
#include "button.h"
#include "main_menu.h"
#include <QGraphicsTextItem>

Game::Game() : QGraphicsView() {
  setFixedSize(1280, 720);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  SetScene(new MainMenu(this, 1920, 1080, Qt::lightGray));
  show();
}

void Game::SetScene(Scene* scene) {
  delete current_scene;
    setScene(scene);
}

void Game::Exit() {
  close();
}

#include "menu.h"
#include "game.h"
#include "level.h"
#include "button.h"
#include "main_menu.h"

#include <QScrollBar>
#include <QDebug>

Game::Game(QApplication* application) : QGraphicsView(),
                                        application_(application),
                                        full_screen_(false) {
  setFixedSize(1280, 720);

  // Disable scroll events
  scroll_disabler_ = new ScrollDisabler();
  InstallScrollDisabler();

  PushScene(new MainMenu(this, 1280, 720, Menu::kOrangeDefaultBackground_));

  background_music_.playlist->addMedia(QUrl("qrc:/sounds/sounds/Big Rock.mp3"));
  background_music_.playlist->setPlaybackMode(QMediaPlaylist::Loop);
  background_music_.player->setPlaylist(background_music_.playlist);
  SetMusicVolume(default_volume_);
  background_music_.player->play();

  show();
}

void Game::PushScene(Scene* scene) {
  if (!scenes_.empty()) {
    scenes_.top()->Pause();
  }
  setScene(scene);
  scenes_.push(scene);
  scenes_.top()->Unpause();
}

void Game::PopScene() {
  scenes_.top()->Pause();
  if (scenes_.size() == 1) {
    application_->quit();
    return;
  }
  scenes_.top()->deleteLater();
  scenes_.pop();
  setScene(scenes_.top());
  scenes_.top()->Unpause();
}

void Game::InstallScrollDisabler() {
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  verticalScrollBar()->installEventFilter(scroll_disabler_);
  horizontalScrollBar()->installEventFilter(scroll_disabler_);
}

void Game::RemoveScrollDisabler() {
  setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  verticalScrollBar()->removeEventFilter(scroll_disabler_);
  horizontalScrollBar()->removeEventFilter(scroll_disabler_);
}

bool Game::IsFullScreen()
{
  return full_screen_;
}

void Game::ChangeScreenState()
{
  full_screen_ = !full_screen_;
}

void Game::SetMusicVolume(int new_volume) {
  background_music_.player->setVolume(new_volume);
}

int Game::GetMusicVolume() {
  return background_music_.player->volume();
}

bool Game::ScrollDisabler::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::Wheel) return true;
  return false;
}

Game::BackgroundMusic::~BackgroundMusic() {
  delete player;
  delete playlist;
}

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
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Disable scroll events
  scroll_disabler_ = new ScrollDisabler();
  verticalScrollBar()->installEventFilter(scroll_disabler_);

  PushScene(new MainMenu(this, 1280, 720, Menu::kOrangeDefaultBackground_));

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
  verticalScrollBar()->installEventFilter(scroll_disabler_);
}

void Game::RemoveScrollDisabler() {
  setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  verticalScrollBar()->removeEventFilter(scroll_disabler_);
}

bool Game::IsFullScreen()
{
  return full_screen_;
}

void Game::ChangeScreenState()
{
  full_screen_ = !full_screen_;
}

bool Game::ScrollDisabler::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::Wheel) return true;
  return false;
}

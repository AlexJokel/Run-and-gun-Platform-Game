#include "menu.h"
#include "game.h"
#include "level.h"
#include "button.h"
#include "main_menu.h"

#include <QScrollBar>
#include <QDebug>

Game::Game(QApplication* application) : QGraphicsView(),
                                        application_(application) {
  setFixedSize(1280, 720);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  /// Disable scroll events of scrollbars
  auto scroll_disabler = new ScrollDisabler();
  horizontalScrollBar()->installEventFilter(scroll_disabler);
  verticalScrollBar()->installEventFilter(scroll_disabler);
  installEventFilter(scroll_disabler);

  PushScene(new MainMenu(this, 1920, 1080, Menu::kOrangeDefaultBackground_));

  show();
}

void Game::PushScene(Scene* scene) {
  setScene(scene);
  scenes_.push(scene);
}

void Game::PopScene() {
  if (scenes_.size() == 1) {
    application_->quit();
    return;
  }
  delete scenes_.top();
  scenes_.pop();
  setScene(scenes_.top());
  centerOn(sceneRect().center());
}

bool Game::ScrollDisabler::eventFilter(QObject*, QEvent* event) {
  for (const auto& type : {QEvent::KeyPress,
                           QEvent::KeyRelease,
                           QEvent::Wheel}) {
    if (event->type() == type) return true;
  }
  return false;
}

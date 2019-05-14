#include "main_menu.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"
#include "scene.h"
#include "cssstylestorage.h"

MainMenu::MainMenu(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
  auto layout = new QVBoxLayout();

  /// writing title
  title_text_ = new QGraphicsTextItem("DOKA 2");
  title_text_->setFont(QFont("Times", 150));
  title_text_->setPos(this->width() / 2 -
                      title_text_->boundingRect().width() / 2, 0);
  addItem(title_text_);

  /// creating Play button
  auto play_button = new Button("PLAY", 400, 100);
  play_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(play_button, &Button::clicked, this, [&] {
      Game()->PushScene(new PickLevelMenu(Game(), 1280, 720,
                                          kOrangeDefaultBackground_, 1, 4));
  });
  layout->addWidget(play_button);

  /// creating Settings button
  auto settings_button = new Button("SETTINGS", 400, 100);
  settings_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  layout->addWidget(settings_button);

  /// creating Quit button
  auto quit_button = new Button("QUIT", 400, 100);
  quit_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());

  QObject::connect(quit_button, &Button::clicked, Game(), &Game::PopScene);
  layout->addWidget(quit_button);

  menu_button_block_->setLayout(layout);
  MoveMenuBlock(430, 300);
  addWidget(menu_button_block_);
}

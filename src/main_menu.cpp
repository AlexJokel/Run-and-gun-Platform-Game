#include "main_menu.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"
#include "scene.h"
#include "cssstylestorage.h"
#include "settings.h"
#include "fileinitializationhelper.h"

#include "QDebug"

MainMenu::MainMenu(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
  auto layout = new QVBoxLayout();

  const int button_width = 400;
  const int button_height = 85;

  /// writing title
  title_text_ = new QGraphicsTextItem("DOKA 2");
  QFont title_font("Verdana", 150);
  title_font.setBold(true);
  title_text_->setFont(title_font);
  title_text_->setPos(this->width() / 2 -
                      title_text_->boundingRect().width() / 2, -20);
  addItem(title_text_);

  /// creating Play button
  auto play_button = new Button("PLAY", button_width, button_height);
  play_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(play_button, &Button::clicked, this, [&] {
      Game()->PushScene(new PickLevelMenu(Game(), 1280, 720,
                                          kOrangeDefaultBackground_, 1, 4));
  });
  layout->addWidget(play_button);

  /// Create New Game button
  auto new_game_button = new Button("NEW GAME", button_width, button_height);
  new_game_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(new_game_button, &Button::clicked,
                   [&, play_button](){
    FileInitializationHelper::CreateOpenLevelMap();
    emit play_button->clicked();
  });
  layout->addWidget(new_game_button);

  /// creating Settings button
  auto settings_button = new Button("SETTINGS", button_width, button_height);
  settings_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(settings_button, &Button::clicked, this, [&] {
      Game()->PushScene(new Settings(Game(), 1280, 900,
                                     kOrangeDefaultBackground_));
  });
  layout->addWidget(settings_button);

  /// creating Quit button
  auto quit_button = new Button("QUIT", button_width, button_height);
  quit_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());

  QObject::connect(quit_button, &Button::clicked, Game(), &Game::PopScene);
  layout->addWidget(quit_button);

  menu_button_block_->setLayout(layout);
  MoveMenuBlock(430, 275);
  addWidget(menu_button_block_);

  /// Check for settings_state file
  QFile file("settings_state.dat");
  if (!file.exists()) {
    qCritical() << "Initial settings state file was created!\n";
    FileInitializationHelper::SaveSettings("settings_state.dat");
  }
  LevelLoader("settings_state.dat").LoadSettings(game);
}

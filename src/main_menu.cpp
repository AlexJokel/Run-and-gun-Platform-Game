#include <QVBoxLayout>

#include "main_menu.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"
#include "scene.h"
#include "cssstylestorage.h"

MainMenu::MainMenu(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
  /// writing title
  title_text_ = new QGraphicsTextItem("DOKA 2");
  QFont title_font("comic sans", 200);
  title_text_->setFont(title_font);
  auto title_x = this->width() / 2 - title_text_->boundingRect().width() / 2;
  auto title_y = 150;
  title_text_->setPos(title_x, title_y);
  addItem(title_text_);

  /// creating Play button
  auto play_button = new Button("PLAY");
  play_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  qint32 button_x = static_cast<qint32>(this->width() / 2 - play_button->size().width() / 2);
  qint32 button_y = 500;
  play_button->move(button_x, button_y);
  QObject::connect(play_button, &Button::clicked, this, [&]{
      Game()->PushScene(new PickLevelMenu(Game(), 1920, 1080, kGreenDefaultBackground_));
    });
  addWidget(play_button);
  buttons_.append(play_button);

  /// creating Settings button
  auto settings_button = new Button("SETTINGS");
  settings_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  button_y = 600;
  settings_button->move(button_x, button_y);
  addWidget(settings_button);
  buttons_.append(settings_button);

  /// creating Quit button
  auto quit_button = new Button("QUIT");
  quit_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  button_y = 700;
  quit_button->move(button_x, button_y);
  QObject::connect(quit_button, &Button::clicked, Game(), &Game::PopScene);
  addWidget(quit_button);
  buttons_.append(quit_button);
}

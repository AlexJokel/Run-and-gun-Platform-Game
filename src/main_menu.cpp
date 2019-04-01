#include "main_menu.h"
#include "game.h"
#include "level.h"
#include "scene.h"

MainMenu::MainMenu(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
  /// writing title
  title_text_ = new QGraphicsTextItem(QString("DOKA 2"));
  QFont titleFont("comic sans", 200);
  title_text_->setFont(titleFont);
  int txPos = this->width() / 2 - title_text_->boundingRect().width() / 2;
  int tyPos = 150;
  title_text_->setPos(txPos, tyPos);
  addItem(title_text_);

  /// creating Play button
  Button* play_button_ = new Button(QString("PLAY"));
  int bxPos = this->width() / 2 - play_button_->boundingRect().width() / 2;
  int byPos = 500;
  play_button_->setPos(bxPos, byPos);
  QObject::connect(play_button_, &Button::clicked, this->Game(),
                   [this]{Game()->SetScene(new Level(this->Game(), 1920, 1080));}
  );
  addItem(play_button_);
  buttons_.push_back(play_button_);

  /// creating Settings button
  Button* settings_button_ = new Button(QString("SETTINGS"));
  bxPos = this->width() / 2 - settings_button_->boundingRect().width() / 2;
  byPos = 600;
  settings_button_->setPos(bxPos, byPos);
  addItem(settings_button_);
  buttons_.push_back(settings_button_);

  /// creating Quit button
  Button* quit_button_ = new Button(QString("QUIT"));
  bxPos = this->width() / 2 - quit_button_->boundingRect().width() / 2;
  byPos = 700;
  quit_button_->setPos(bxPos, byPos);
  QObject::connect(quit_button_, &Button::clicked, this->Game(), &Game::Exit);
  addItem(quit_button_);
  buttons_.push_back(quit_button_);
}

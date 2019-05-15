#include "settings.h"
#include "main_menu.h"
#include "game.h"
#include "player.h"
#include "level.h"
#include "scene.h"
#include "settings_button.h"
#include "picklevelmenu.h"
#include "cssstylestorage.h"
#include "soundeffectstorage.h"

#include <QScrollBar>
#include <QSlider>

const QMap<int, QString> Settings::code_to_key = {
  {32, "Space"}, {16777220, "Enter"},
  {16777221, "NumEnter"},{16777251, "Alt"},
  {16777248, "Shift"}, {16777249, "Ctrl"},
  {16777217, "Tab"}, {16777264, "F1"},
  {16777265, "F2"}, {16777266, "F3"},
  {16777267, "F4"}, {16777268, "F5"},
  {16777269, "F6"}, {16777270, "F7"},
  {16777271, "F8"}, {16777272, "F9"},
  {16777273, "F10"}, {16777274, "F11"},
  {16777275, "F12"}, {16777222, "Insert"},
  {16777223, "Delete"}, {16777238, "PgUp"},
  {16777239, "PgDn"}, {16777232, "Home"},
  {16777233, "Home"}, {16777235, "🡹"},
  {16777234, "🡸"}, {16777237, "🡻"},
  {16777236, "🡺"}, {16777219, "Backspace"}
};

Settings::Settings(class Game* game, qreal width, qreal height, QColor color)
  : Menu(game, width, height, color) {
  auto layout = new QVBoxLayout();
  //Game()->RemoveScrollDisabler();

  // creating a title
  title_text_ = new QGraphicsTextItem("SETTINGS");
  title_text_->setFont(QFont("Comic", 70));
  title_text_->setPos(this->width() / 2 -
                      title_text_->boundingRect().width() / 2, -25);
  addItem(title_text_);

  // creating controls buttons
  AddButtonToLayout(layout, 200, 100, "Left");
  AddButtonToLayout(layout, 200, 100, "Right");
  AddButtonToLayout(layout, 200, 100, "Jump");

  // creating screen button
  auto screen_button = new Button((Game()->IsFullScreen()) ? "YES" : "NO", 200, 100);
  layout->addWidget(screen_button);
  screen_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(screen_button, &Button::clicked, this, [=]() {
    if (Game()->IsFullScreen()) {
      screen_button->setText("NO");
      game->showNormal();
      game->scale(0.6666,0.6666);
    } else {
      screen_button->setText("YES");
      game->showFullScreen();
      game->scale(1.5,1.5);
    }
    game->ChangeScreenState();
  });

  menu_button_block_->setLayout(layout);
  MoveMenuBlock(700, 110);
  addWidget(menu_button_block_);

  // creating sliders
  auto music_slider = new QSlider(Qt::Horizontal);
  QObject::connect(music_slider, &QSlider::valueChanged,
                   Game(), &Game::SetMusicVolume);
  music_slider->setMaximum(100);
  music_slider->setValue(Game()->default_volume_);
  music_slider->move(712, 580);
  addWidget(music_slider);

  auto effects_slider = new QSlider(Qt::Horizontal);
  QObject::connect(effects_slider, &QSlider::valueChanged,
                   &SoundEffectStorage::SetSoundVolume);
  effects_slider->setMaximum(100);
  effects_slider->setValue(effects_slider->maximum());
  effects_slider->move(712, 650);
  addWidget(effects_slider);

  // creating exit button
  auto exit_button = new Button("EXIT", 100, 100);
  exit_button->move(50,40);
  exit_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  addWidget(exit_button);
  QObject::connect(exit_button, &Button::clicked, this, [&]() {
    Game()->PopScene();
  });

  // creating text for controls
  AddText("Left", 380, 125, {"comic", 30});
  AddText("Right", 380, 235, {"comic", 30});
  AddText("Jump", 380, 345, {"comic", 30});
  AddText("Full screen", 380, 455, {"comic", 30});
  AddText("Music", 380, 550, {"comic", 30});
  AddText("Effects", 380, 620, {"comic", 30});
}

void Settings::AddText(QString text, qreal width, qreal height, QFont font) {
  auto button_text = new QGraphicsTextItem(text);
  button_text->setFont(font);
  button_text->setPos(width, height);
  addItem(button_text);
  return;
}

void Settings::AddButtonToLayout(QVBoxLayout* layout, qint32 width,
                                 qint32 height, QString key) {
  auto button = new SettingsButton(
      (code_to_key.count(static_cast<int>(Player::controls_map_[key])) == 0)
      ? static_cast<QString>(Player::controls_map_[key])
      : code_to_key[static_cast<int>(Player::controls_map_[key])],
                                 width, height, key);
  button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  layout->addWidget(button);
}

Settings::~Settings() {
 // Game()->InstallScrollDisabler();
}

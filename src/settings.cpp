#include "settings.h"
#include "main_menu.h"
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
  LevelLoader level_loader_("settings_state.dat");
  auto layout = new QVBoxLayout();
  Game()->RemoveScrollDisabler();

  // creating a title
  title_text_ = new QGraphicsTextItem("SETTINGS");
  QFont title_font("Verdana", 80);
  title_font.setBold(true);
  title_text_->setFont(title_font);
  title_text_->setPos(this->width() / 2 -
                      title_text_->boundingRect().width() / 2, 20);
  addItem(title_text_);

  // creating controls buttons
  AddButtonToLayout(layout, 200, 100, "Left", game);
  AddButtonToLayout(layout, 200, 100, "Right", game);
  AddButtonToLayout(layout, 200, 100, "Jump", game);

  // creating screen button
  auto screen_button = new Button((Game()->IsFullScreen()) ? "YES" : "NO", 200, 100);
  layout->addWidget(screen_button);
  screen_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(screen_button, &Button::clicked, this, [=]() {
    if (Game()->IsFullScreen()) {
      screen_button->setText("NO");
      game->RemoveFullScreenMode();
    } else {
      screen_button->setText("YES");
      game->SetFullScreenMode();
    }
    screen_button->Changed();
  });

  QObject::connect(screen_button, &Button::Changed, this, [=]() {
    SettingsLoader(game, "settings_state.dat").SaveSettings();
  });
  menu_button_block_->setLayout(layout);
  MoveMenuBlock(700, 200);
  addWidget(menu_button_block_);

  // creating sliders
  auto music_slider = new QSlider(Qt::Horizontal);
  QObject::connect(music_slider, &QSlider::valueChanged,
                   this, [=]() {
    Game()->SetMusicVolume(music_slider->value());
    SettingsLoader(game, "settings_state.dat").SaveSettings();
  });
  music_slider->setMaximum(100);
  music_slider->setValue(Game()->GetMusicVolume());
  music_slider->move(712, 650);
  music_slider->setStyleSheet(
      CssStyleStorage::GetInstance().GetSettingsSliderStyle());
  addWidget(music_slider);

  auto effects_slider = new QSlider(Qt::Horizontal);
  QObject::connect(effects_slider, &QSlider::valueChanged,
                   [=]() {
    SoundEffectStorage::SetSoundVolume(effects_slider->value());
    SettingsLoader(game, "settings_state.dat").SaveSettings();
   });

  effects_slider->setMaximum(100);
  effects_slider->setValue(SoundEffectStorage::GetSoundVolume());
  effects_slider->move(712, 715);
  effects_slider->setStyleSheet(
      CssStyleStorage::GetInstance().GetSettingsSliderStyle());
  addWidget(effects_slider);

  // creating exit button
  auto exit_button = new Button("EXIT", 300, 100);
  exit_button->move(500,790);
  exit_button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  addWidget(exit_button);
  QObject::connect(exit_button, &Button::clicked, this, [&]() {
    Game()->PopScene();
  });



  // creating text for controls
  AddText("Left", 380, 215, {"Verdana", 30});
  AddText("Right", 380, 325, {"Verdana", 30});
  AddText("Jump", 380, 435, {"Verdana", 30});
  AddText("Full screen", 380, 545, {"Verdana", 30});
  AddText("Music", 380, 640, {"Verdana", 30});
  AddText("Effects", 380, 710, {"Verdana", 30});
}

void Settings::AddText(QString text, qreal width, qreal height, QFont font) {
  auto button_text = new QGraphicsTextItem(text);
  button_text->setFont(font);
  button_text->setPos(width, height);
  addItem(button_text);
  return;
}

void Settings::AddButtonToLayout(QVBoxLayout* layout, qint32 width,
                                 qint32 height, QString key, class Game* game) {
  auto button = new SettingsButton(
      (code_to_key.count(static_cast<int>(Player::controls_map_[key])) == 0)
      ? static_cast<QString>(Player::controls_map_[key])
      : code_to_key[static_cast<int>(Player::controls_map_[key])],
                                 width, height, key);
  button->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(button, &Button::Changed, this, [=]() {
    SettingsLoader(game, "settings_state.dat").SaveSettings();
  });
  layout->addWidget(button);
}

Settings::~Settings() {
  Game()->InstallScrollDisabler();
}

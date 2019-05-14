#include "settings.h"
#include "main_menu.h"
#include "game.h"
#include "player.h"
#include "level.h"
#include "scene.h"
#include "settings_button.h"
#include "picklevelmenu.h"
#include "cssstylestorage.h"

#include <QScrollBar>

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
    Game()->RemoveScrollDisabler();

    // creating a title
    title_text_ = new QGraphicsTextItem("SETTINGS");
    title_text_->setFont(QFont("Comic", 70));
    title_text_->setPos(this->width() / 2 -
                        title_text_->boundingRect().width() / 2, 0);
    addItem(title_text_);

    // creating controls buttons
    AddButtonToLayout(layout, 200, 100, "Left");
    AddButtonToLayout(layout, 200, 100, "Right");
    AddButtonToLayout(layout, 200, 100, "Jump");

    menu_button_block_->setLayout(layout);
    MoveMenuBlock(900, 150);
    addWidget(menu_button_block_);
}

void Settings::AddText(QString text, qreal width, qreal height, QColor color) {
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
  Game()->InstallScrollDisabler();
}

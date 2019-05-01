#include "settings_button.h"

SettingsButton::SettingsButton(const QString& title, qint32 width, qint32 height,  QString key,
                               QWidget* parent) :
    Button (title, width, height, parent),
    key_(key) {}

void SettingsButton::ChangeControl(Qt::Key new_key) {
    Player::controls_map_[key_] = new_key;
}

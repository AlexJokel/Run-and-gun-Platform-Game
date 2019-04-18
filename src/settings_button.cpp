#include "settings_button.h"

SettingsButton::SettingsButton(QString name, QGraphicsItem *parent) :
    Button (name, parent),
    key_(name) {}

void SettingsButton::ChangeControl(Qt::Key new_key) {
    Player::controls_map_[key_] = new_key;
}

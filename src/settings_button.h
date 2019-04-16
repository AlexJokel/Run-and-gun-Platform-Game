#ifndef SETTINGS_BUTTON_H
#define SETTINGS_BUTTON_H
#include "button.h"
#include "player.h"

class SettingsButton : public Button {
public:
    SettingsButton(QString name, QGraphicsItem* parent = nullptr);
    void ChangeControl(Qt::Key) {}

protected:
    QString key_;
};

#endif // SETTINGS_BUTTON_H

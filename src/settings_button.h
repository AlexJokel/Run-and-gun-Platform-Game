#ifndef SETTINGS_BUTTON_H
#define SETTINGS_BUTTON_H
#include "button.h"
#include "player.h"

class SettingsButton : public Button {
public:
    SettingsButton(const QString& title, qint32 width, qint32 height, QString key,
                   QWidget* parent = nullptr);
    void ChangeControl(Qt::Key);

protected:
    QString key_;
};

#endif // SETTINGS_BUTTON_H

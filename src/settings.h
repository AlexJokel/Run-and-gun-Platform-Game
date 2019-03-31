#ifndef SETTINGS_H
#define SETTINGS_H

#include "menu.h"

class Settings : public Menu {
public:
    Settings(class Game*, qreal width, qreal height, QColor);
    qreal AddText(QString, qreal width, qreal height, QFont, QColor);
    qreal AddButton(QString, qreal width, qreal height);
};

#endif // SETTINGS_H

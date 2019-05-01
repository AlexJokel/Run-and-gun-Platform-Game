#ifndef SETTINGS_H
#define SETTINGS_H
#include "menu.h"

#include <QVBoxLayout>

class Settings : public Menu {
public:
    Settings(class Game*, qreal width, qreal height, QColor);
    void AddText(QString, qreal width, qreal height, QFont, QColor);
    void AddButton(QVBoxLayout* layout, QString name, qreal width, qreal height, QString key);
};

#endif // SETTINGS_H

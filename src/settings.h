#ifndef SETTINGS_H
#define SETTINGS_H
#include "menu.h"
#include <QVBoxLayout>

class Settings : public Menu {
public:
    Settings(class Game*, qreal width, qreal height, QColor);
    void AddText(QString, qreal width, qreal height, QFont, QColor);
    void AddButtonToLayout(QVBoxLayout* layout, QString name, qint32 width, qint32 height, QString key);
};

#endif // SETTINGS_H

#ifndef SETTINGS_H
#define SETTINGS_H
#include "menu.h"
#include <QVBoxLayout>

class Settings : public Menu {
public:
    Settings(class Game*, qreal width, qreal height, QColor);

    void AddText(QString, qreal width, qreal height, QColor);
    void AddButtonToLayout(QVBoxLayout* layout, qint32 width, qint32 height, QString key);

    ~Settings() override;
private:
  static const QMap<int, QString> code_to_key;
};

#endif // SETTINGS_H

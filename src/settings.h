#ifndef SETTINGS_H
#define SETTINGS_H
#include "menu.h"
#include <QVBoxLayout>
#include "game.h"
#include "settingsloader.h"

class Settings : public Menu {
public:
  Settings(class Game*, qreal width, qreal height, QColor);

  void AddText(QString, qreal width, qreal height, QFont);
  void AddButtonToLayout(QVBoxLayout* layout, qint32 width, qint32 height, QString key, class Game* game);

  ~Settings() override;

protected: signals:
  void Changed() const;

private:
  static const QMap<int, QString> code_to_key;
};

#endif // SETTINGS_H

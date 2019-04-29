#ifndef CSSSTYLESTORAGE_H
#define CSSSTYLESTORAGE_H

#include <QMap>

class CssStyleStorage {
public:
  static CssStyleStorage& GetInstance();

  const QString& GetMenuButtonStyle() const;
  const QString& GetLockedButtonStyle() const;
private:
  CssStyleStorage();
  ~CssStyleStorage();

  CssStyleStorage(const CssStyleStorage&) = delete;
  CssStyleStorage& operator=(const CssStyleStorage&) = delete;

  QString menu_button_style_;
  QString locked_button_style_;
};

#endif // CSSSTYLESTORAGE_H
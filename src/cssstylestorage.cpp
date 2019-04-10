#include <QFile>
#include <QDebug>

#include "cssstylestorage.h"

CssStyleStorage& CssStyleStorage::GetInstance() {
  static CssStyleStorage storage;
  return storage;
}

const QString& CssStyleStorage::GetMenuButtonStyle() const {
  return menu_button_style_;
}

CssStyleStorage::CssStyleStorage() {
  QFile input_file(":/style/styles/main_menu_button.css");
  if (input_file.open(QIODevice::ReadOnly)) {
    menu_button_style_ = input_file.readAll();
    input_file.close();
    qDebug() << "loaded!\n";
  }
}

CssStyleStorage::~CssStyleStorage() {}

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

const QString& CssStyleStorage::GetLockedButtonStyle() const {
  return locked_button_style_;
}

const QString& CssStyleStorage::GetSettingsSliderStyle() const {
  return settings_slider_;
}

CssStyleStorage::CssStyleStorage() {
  QFile menu_button_file(":/styles/styles/main_menu_button.css");
  if (menu_button_file.open(QIODevice::ReadOnly)) {
    menu_button_style_ = menu_button_file.readAll();
    menu_button_file.close();
  } else {
    qCritical() << "Failed to load main_menu_button.css";
  }

  QFile locked_button_file(":/styles/styles/locked_button_style.css");
  if (locked_button_file.open(QIODevice::ReadOnly)) {
    locked_button_style_ = locked_button_file.readAll();
    locked_button_file.close();
  } else {
    qCritical() << "Failed to load locked_button_style.css";
  }

  QFile settings_slider_file(":/styles/styles/settings_slider.css");
  if (settings_slider_file.open(QIODevice::ReadOnly)) {
    settings_slider_ = settings_slider_file.readAll();
    settings_slider_file.close();
  } else {
    qCritical() << "Failed to load settings_slider.css";
  }
}

CssStyleStorage::~CssStyleStorage() {}

#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H
#include "levelloader.h"

class SettingsLoader : public LevelLoader {
public:
  SettingsLoader(Game*, const QString& file_name = "");
  void SaveSettings() const;
  void LoadSettings() const;
protected:
  Game* game_;
};

#endif // SETTINGSLOADER_H

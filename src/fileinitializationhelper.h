#ifndef FILEINITIALIZATIONHELPER_H
#define FILEINITIALIZATIONHELPER_H

#include "game.h"

class FileInitializationHelper {
public:
  /// Path is specified relatively to build directory
  /// After creating of the level don't forget to add it to resouces
  static void CreateFirstLevel(class Game* game,
                               const QString& file_name = "level0.dat");
  static void CreateSecondLevel(class Game* game,
                               const QString& file_name = "level1.dat");
  static void CreateOpenLevelMap(const QString& file_name = "open_levels_state.dat");

  static void SaveSettings(const QString& file_name = "settings_state.dat");
};

#endif // FILEINITIALIZATIONHELPER_H

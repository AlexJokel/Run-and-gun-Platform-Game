#ifndef FILEINITIALIZATIONHELPER_H
#define FILEINITIALIZATIONHELPER_H

#include "game.h"

class FileInitializationHelper {
public:
  /// Path is specified relatively to build directory
  static void CreateLevel(class Game* game, const QString& file_name = "level1.dat");
  static void CreateOpenLevelMap(const QString& file_name = "open_levels_state.dat");
};

#endif // FILEINITIALIZATIONHELPER_H

#include "fileinitializationhelper.h"

#include "level.h"
#include "levelloader.h"

void FileInitializationHelper:: CreateLevel(class Game* game) {
  auto level = new Level(game, 1920, 1080);
  /// Player initialization
  level->SetPlayer(new Player(level, 3, 3));
  /// Create floor
  level->AppendGround(new Ground(level,
                        0,
                        level->PixelsToMeters(level->height()) - 1,
                        level->PixelsToMeters(level->width()), 1));
  /// Create walls
  level->AppendGround(new Ground(level,
                         0,
                         0,
                         1,
                         level->PixelsToMeters(level->height())));
  level->AppendGround(new Ground(level,
                         level->PixelsToMeters(level->width()) - 1,
                         0,
                         1,
                         level->PixelsToMeters(level->height())));
  LevelLoader loader("level1.dat");
  loader.WriteLevel(level);
  delete level;
}

void FileInitializationHelper::CreateOpenLevelMap() {
  QMap<qint32, bool> open_state;
  for (qint32 i = 0; i < 15; ++i) {
    open_state[i] = false;
  }
  open_state[0] = true;
  open_state[1] = true;

  QFile file("open_levels_state.dat");
  file.open(QIODevice::WriteOnly);
  QDataStream output(&file);
  output << open_state;
  file.close();
}

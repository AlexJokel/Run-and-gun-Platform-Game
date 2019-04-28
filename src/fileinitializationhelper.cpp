#include "fileinitializationhelper.h"

#include "level.h"
#include "levelloader.h"
#include "staticenemy.h"
#include "roamingenemy.h"

void FileInitializationHelper:: CreateFirstLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game, 1920, 1080);
  /// Player initialization
  level->SetPlayer(new Player(level, {3, 3}));
  /// Create floor
  level->AppendGround(new Ground(level,
                        {0, level->PixelsToMeters(level->height()) - 1},
                        {level->PixelsToMeters(level->width()), 1}));
  /// Create walls
  level->AppendGround(new Ground(level,
                         {0, 0},
                         {1, level->PixelsToMeters(level->height())}));
  level->AppendGround(new Ground(level,
                         {level->PixelsToMeters(level->width()) - 1, 0},
                         {1, level->PixelsToMeters(level->height())}));

  /// Enemy initialization
  level->AppendEnemy(new StaticEnemy(level, {7, 3}));
  level->AppendEnemy(new RoamingEnemy(level, {10, 3}, {8, 12}));

  LevelLoader loader(file_name);
  loader.WriteLevel(level);
  delete level;
}

void FileInitializationHelper:: CreateSecondLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game, 1920, 1080);
  /// Player initialization
  level->SetPlayer(new Player(level, {3, 9}));

  /// Create floor
  level->AppendGround(new Ground(level,
                        {0, level->PixelsToMeters(level->height()) - 1},
                        {level->PixelsToMeters(level->width()), 1}));
  /// Create walls
  level->AppendGround(new Ground(level,
                         {0, 0},
                         {1, level->PixelsToMeters(level->height())}));
  level->AppendGround(new Ground(level,
                         {level->PixelsToMeters(level->width()) - 1, 0},
                         {1, level->PixelsToMeters(level->height())}));

  /// Create platforms
  level->AppendGround(new Ground(level, {10, 8}, {4, 0.5}));
  level->AppendGround(new Ground(level, {15, 6}, {6, 0.5}));
  level->AppendGround(new Ground(level, {0, 4},
  {level->PixelsToMeters(level->width()) - 4, 0.5}));

  /// Enemy initialization
  level->AppendEnemy(new StaticEnemy(level, {7, 3}));
  level->AppendEnemy(new StaticEnemy(level, {16, 6}));
  level->AppendEnemy(new RoamingEnemy(level, {10, 3}, {8, 12}));
  level->AppendEnemy(new RoamingEnemy(level, {10, 9}, {8, 12}));

  LevelLoader loader(file_name);
  loader.WriteLevel(level);
  delete level;
}

void FileInitializationHelper::CreateOpenLevelMap(const QString& file_name) {
  QMap<qint32, bool> open_state;
  for (qint32 i = 0; i < 15; ++i) {
    open_state[i] = false;
  }
  open_state[0] = true;
  open_state[1] = true;

  QFile file(file_name);
  file.open(QIODevice::WriteOnly);
  QDataStream output(&file);
  output << open_state;
  file.close();
}

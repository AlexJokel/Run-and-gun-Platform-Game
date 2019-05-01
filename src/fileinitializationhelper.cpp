#include "fileinitializationhelper.h"

#include "level.h"
#include "levelloader.h"
#include "staticenemy.h"
#include "roamingenemy.h"
#include "finishpoint.h"

void FileInitializationHelper:: CreateFirstLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game);

  /// Player initialization
  level->SetPlayer(new Player(level, {1, 6}));
  /// Create floor
  level->AppendGround(new Ground(level,
                                 {0, 6.5},
                                 {20, 1}));

  /// Create walls
  level->AppendGround(new Ground(level,
                                 {0, 0},
                                 {0.5, 3.5}));
  level->AppendGround(new Ground(level,
                                 {19.5, 0},
                                 {0.5, 3.5}));
  level->AppendGround(new Ground(level,
                                 {0, 3.5},
                                 {0.01f, 3}));
  level->AppendGround(new FinishPoint(level,
                                      {19.99f, 3.5},
                                      {0.01f, 3}));

  /// Enemy initialization
  level->AppendEnemy(new StaticEnemy(level, {7, 6}));
  level->AppendEnemy(new RoamingEnemy(level, {10, 6}, {8, 12}));

  LevelLoader loader(file_name);
  loader.WriteLevel(level);
  delete level;
}

void FileInitializationHelper:: CreateSecondLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game);
  /// Player initialization
  level->SetPlayer(new Player(level, {3, 9}));

  /// Create floor
  level->AppendGround(new Ground(level,
                        {0, 9.5},
                        {20, 0.5}));
  /// Create walls
  level->AppendGround(new Ground(level,
                         {0, 0},
                         {0.5, 1}));
  level->AppendGround(new FinishPoint(level,
                                      {0, 1},
                                      {0.01f, 3}));
  level->AppendGround(new Ground(level,
                         {0, 4.5},
                         {0.5, 2.5}));
  level->AppendGround(new Ground(level,
                         {0, 6.5},
                         {0.01f, 3}));
  level->AppendGround(new Ground(level,
                         {19.5, 0},
                         {0.5, 9.5}));

  /// Create platforms
  level->AppendGround(new Ground(level, {0, 4}, {16, 0.5}));
  level->AppendGround(new Ground(level, {9.5, 7.5}, {4, 0.5}));
  level->AppendGround(new Ground(level, {15, 6}, {5, 0.5}));

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

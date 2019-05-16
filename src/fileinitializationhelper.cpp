#include "fileinitializationhelper.h"

#include "level.h"
#include "levelloader.h"
#include "staticenemy.h"
#include "roamingenemy.h"
#include "finishpoint.h"
#include "player.h"
#include "soundeffectstorage.h"

void FileInitializationHelper:: CreateFirstLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game, 4);

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
  auto level = new Level(game, 10);
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

void FileInitializationHelper::CreateThirdLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game, 20);
  level->SetPlayer(new Player(level, {2, 9.5}));

  /// Bounds
  level->AppendGround(new Ground(level, {0, 10}, {20, 0.5}));
  level->AppendGround(new Ground(level, {0, -3}, {0.5, 13.5}));
  level->AppendGround(new Ground(level, {20, -0.5}, {0.5, 10.5}));

  /// Platforms
  level->AppendGround(new Ground(level, {5, 7.5}, {6, 0.5}));
  level->AppendGround(new Ground(level, {14, 7.5}, {6, 0.5}));
  level->AppendGround(new Ground(level, {9, 5}, {6, 0.5}));
  level->AppendGround(new Ground(level, {2, 2}, {6, 0.5}));
  level->AppendGround(new Ground(level, {11, -0.5}, {9, 0.5}));
  level->AppendGround(new FinishPoint(level, {20, -3}, {0.01f, 3}));

  /// Enemies
  level->AppendEnemy(new StaticEnemy(level, {7, 9.5}));
  level->AppendEnemy(new RoamingEnemy(level, {11, 9.5}, {9.5, 17.5}));

  /// 2nd layer enemies
  level->AppendEnemy(new RoamingEnemy(level, {6, 6.5}, {5, 10.5}));
  level->AppendEnemy(new RoamingEnemy(level, {15, 6.5}, {14, 19}));

  /// 3rd and 4th layer enemies
  level->AppendEnemy(new RoamingEnemy(level, {9, 4.5}, {9.5, 14.5}));
  level->AppendEnemy(new RoamingEnemy(level, {13, -1}, {11, 19}));

  LevelLoader loader(file_name);
  loader.WriteLevel(level);
  delete level;
}

void FileInitializationHelper::CreateForthLevel(class Game* game, const QString& file_name) {
  auto level = new Level(game, 35);
  level->SetPlayer(new Player(level, {34, 3.5}));

  /// Bounds
  level->AppendGround(new Ground(level, {20, 0}, {0.5, 24}));
  level->AppendGround(new Ground(level, {70, 0}, {0.5, 12}));
  level->AppendGround(new Ground(level, {70, 15}, {0.5, 9}));
  level->AppendGround(new Ground(level, {20, 24}, {50.5, 0.5}));

  /// Platforms
  level->AppendGround(new Ground(level, {30, 2}, {2, 2}));
  level->AppendGround(new Ground(level, {30, 4}, {5, 0.5}));

  level->AppendGround(new Ground(level, {37, 8.3f}, {5, 0.5}));
  level->AppendGround(new Ground(level, {44, 6}, {7, 0.5}));
  level->AppendGround(new Ground(level, {53, 3}, {17, 0.5}));
  level->AppendGround(new Ground(level, {50, 8.5}, {20, 0.5}));

  level->AppendGround(new Ground(level, {60, 3}, {0.5, 2.5}));    // edge
  level->AppendGround(new Ground(level, {56, 5.5}, {8, 0.5}));

  level->AppendGround(new Ground(level, {20, 9}, {12, 0.5}));
  level->AppendGround(new Ground(level, {38, 11.5}, {32, 0.5}));

  level->AppendGround(new Ground(level, {40, 12}, {0.5, 3.5}));    // edge
  level->AppendGround(new Ground(level, {40, 15.5}, {8, 0.5}));
  level->AppendGround(new Ground(level, {44, 14.5}, {0.5, 2}));    // edge
  level->AppendGround(new Ground(level, {44, 18}, {8, 0.5}));
  level->AppendGround(new Ground(level, {50, 18}, {0.5, 3}));    // edge
  level->AppendGround(new Ground(level, {50, 21}, {8, 0.5}));

  level->AppendGround(new Ground(level, {64, 21}, {3, 0.5})); // path to finish
  level->AppendGround(new Ground(level, {58, 18}, {3, 0.5}));

  level->AppendGround(new Ground(level, {20, 12.5}, {6, 0.5}));
  level->AppendGround(new Ground(level, {26, 12}, {0.5, 2}));    // edge
  level->AppendGround(new Ground(level, {30, 14}, {10, 0.5}));
  level->AppendGround(new Ground(level, {60, 15}, {10.5, 0.5}));

  level->AppendGround(new Ground(level, {20, 18}, {8, 6})); // blocks
  level->AppendGround(new Ground(level, {28, 20}, {10, 4}));
  level->AppendGround(new Ground(level, {38, 22}, {4, 2}));

  level->AppendGround(new FinishPoint(level, {70.5, 12}, {0.01f, 3}));

  /// Enemies
  level->AppendEnemy(new RoamingEnemy(level, {37, 7.5}, {37.5, 41.5}));
  level->AppendEnemy(new RoamingEnemy(level, {44, 6}, {44.5, 50.5}));

  level->AppendEnemy(new RoamingEnemy(level, {60, 3}, {60.5, 69}));

  level->AppendEnemy(new StaticEnemy(level, {63.5, 5.5}));
  level->AppendEnemy(new RoamingEnemy(level, {50, 11.5}, {45, 60}));

  level->AppendEnemy(new StaticEnemy(level, {65, 15.5}));
  //level->AppendEnemy(new StaticEnemy(level, {51.5, 18}));
  level->AppendEnemy(new StaticEnemy(level, {57.5, 21}));

  level->AppendEnemy(new StaticEnemy(level, {24, 14.5}));
  level->AppendEnemy(new StaticEnemy(level, {26, 10}));

  level->AppendEnemy(new StaticEnemy(level, {44, 17})); // hole sniper

  level->AppendEnemy(new StaticEnemy(level, {65.5, 11.5}));

  level->AppendEnemy(new StaticEnemy(level, {64, 13})); // final

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

  QFile file(file_name);
  file.open(QIODevice::WriteOnly);
  QDataStream output(&file);
  output << open_state;
  file.close();
}

void FileInitializationHelper::SaveSettings(const QString &file_name) {
  QFile file(file_name);
  file.open(QIODevice::WriteOnly);
  QDataStream output(&file);
  output << "Jump" << static_cast<int>(Qt::Key_Space);
  output << "Left" << static_cast<int>(Qt::Key_A);
  output << "Right" << static_cast<int>(Qt::Key_D);
  output << "Screen" << 0;
  output << "Music" << 70;
  output << "Effect" << 100;
  file.close();
}

#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QtGlobal>
#include <QDebug>

#include <Box2D/Box2D.h>

#include "game.h"
#include "level.h"
#include "player.h"
#include "ground.h"
#include "levelloader.h"

void CreateLevel(class Game* game) {
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
}

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  /// Game start
  new Game(&application);

  /// Just write level into file using this function
  /// when you do it for the first time
  // CreateLevel(game);

  return application.exec();
}

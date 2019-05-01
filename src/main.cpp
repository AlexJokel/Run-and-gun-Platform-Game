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
#include "fileinitializationhelper.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  /// Game start
  auto game = new Game(&application);
  game->x(); // to suppress 'unused variable' warning

//  FileInitializationHelper::CreateSecondLevel(game,
//      "../Run-and-gun-Platform-Game/resources/levels/level1.dat");

  return application.exec();
}

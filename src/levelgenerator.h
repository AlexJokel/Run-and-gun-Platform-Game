#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "level.h"
#include "game.h"

class LevelGenerator {
public:
  LevelGenerator(qint32 width = 15, qint32 height = 10);

  void SetWidth(qint32 width);
  void SetHeigth(qint32 height);
  qint32 GetWidth() const;
  qint32 GetHeight()  const;

  Level* GenerateRandomLevel(Game* game, qint32 arrows_count);

protected:
  qint32 width_;
  qint32 height_;
};

#endif // LEVELGENERATOR_H

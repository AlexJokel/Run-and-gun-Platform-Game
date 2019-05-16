#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "level.h"
#include "game.h"

class LevelGenerator {
public:
  LevelGenerator(float width = 30.0, float height = 20.0);

  void SetWidth(float width);
  void SetHeigth(float height);
  float GetWidth() const;
  float GetHeight()  const;

  Level* GenerateRandomLevel(Game* game, qint32);

protected:
  float width_;
  float height_;
};

#endif // LEVELGENERATOR_H

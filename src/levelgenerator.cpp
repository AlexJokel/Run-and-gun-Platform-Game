#include "levelgenerator.h"

LevelGenerator::LevelGenerator(qint32 width, qint32 height)
      : width_(width), height_(height) {}

void LevelGenerator::SetWidth(qint32 width) {
  width_ = width;
}

void LevelGenerator::SetHeigth(qint32 height) {
  height_ = height;
}

qint32 LevelGenerator::GetWidth() const {
  return width_;
}

qint32 LevelGenerator::GetHeight() const {
  return height_;
}

Level* LevelGenerator::GenerateRandomLevel(Game* game, qint32 arrows_count) {
  auto level = new Level(game, arrows_count);

  qint32 current_height = height_ / 2;
  for (qint32 column_index = 0; column_index < width_; ++column_index) {
    level->AppendGround(new Ground(level,
        {static_cast<float>(column_index), static_cast<float>(height_ - current_height)},
        {1, static_cast<float>(current_height)}));
  }
  level->setSceneRect({level->MetersToPixels({0, 0}),
                      level->MetersToPixels({static_cast<float>(width_),
                                             static_cast<float>(height_)})});
  return level;
}

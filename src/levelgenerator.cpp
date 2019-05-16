#include <random>
#include <QtGlobal>

#include "levelgenerator.h"

LevelGenerator::LevelGenerator(float width, float height)
      : width_(width), height_(height) {}

void LevelGenerator::SetWidth(float width) {
  width_ = width;
}

void LevelGenerator::SetHeigth(float height) {
  height_ = height;
}

float LevelGenerator::GetWidth() const {
  return width_;
}

float LevelGenerator::GetHeight() const {
  return height_;
}

Level* LevelGenerator::GenerateRandomLevel(Game* game, qint32 arrows_count) {
  auto level = new Level(game, arrows_count);
  level->SetPlayer(new Player(level, {width_ / 2, 0}));

  /// Create walls
  level->AppendGround(new Ground(level, {0, 0}, {1.0, height_}));
  level->AppendGround(new Ground(level, {width_ - 1.0f, 0}, {1.0, height_}));

  const long long seed =
        std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
  std::mt19937 generator(seed);
  std::uniform_real_distribution<float> distribution(-2.9f, 2.9f);

  auto current_height = height_ / 2;
  for (float column = 0.0; column < width_; column += 0.8f) {
    level->AppendGround(new Ground(level,
        {column, height_ - current_height}, {1, current_height}));
    auto jump = distribution(generator);
    current_height += jump;
    qDebug() << current_height << "\n";
    current_height = qMin(current_height, height_ * 0.7f);
    current_height = qMax(current_height, 1.0f);
  }
  level->setSceneRect({level->MetersToPixels({0, 0}),
                      level->MetersToPixels({static_cast<float>(width_),
                                             static_cast<float>(height_)})});
  return level;
}

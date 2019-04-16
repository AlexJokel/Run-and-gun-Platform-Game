#include "levelloader.h"


QDataStream& operator<<(QDataStream& out, b2Vec2 pair) {
  return out << pair.x << pair.y;
}

QDataStream& operator<<(QDataStream& out,
                        Object* object) {
    return out << object->GetPos() << object->GetSize();
}

QDataStream& operator<<(QDataStream& out, Level* level) {
  out << level->GetPlayer();
  auto ground = level->GetGround();
  out << ground.size();
  for (const auto& item : ground) {
    out << item;
  }
  return out;
}

LevelLoader::LevelLoader(const QString& file_name)
  : file_name_(file_name) {}

void LevelLoader::SetFileName(const QString& file_name) {
  file_name_ = file_name;
}

const QString& LevelLoader::GetFileName() {
  return file_name_;
}

Level* LevelLoader::LoadLevel(class Game* game,
                              qreal width, qreal height) {
  auto level = new Level(game, width, height);
  /// Read level player and ground
  return level;
}

void LevelLoader::WriteLevel(Level *level) {
  QFile file(file_name_);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  // serialize level into the file
  out << level;
}

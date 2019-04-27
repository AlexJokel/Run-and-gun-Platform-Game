#include <QDebug>

#include "levelloader.h"


QDataStream& operator<<(QDataStream& out, const b2Vec2& pair) {
  return out << pair.x << pair.y;
}

QDataStream& operator>>(QDataStream& in, b2Vec2& pair) {
  return in >> pair.x >> pair.y;
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

  QFile file(file_name_);
  if(!file.open(QIODevice::ReadOnly)) {
    qDebug() << "LevelLoader::LoadLevel: File can't be opened for reading!\n";
    return nullptr;
  }
  QDataStream input(&file);
  // read level from the file
  b2Vec2 pos, size;

  input >> pos >> size;
  level->SetPlayer(new Player(level, pos.x, pos.y,
                              PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
  qint32 count;
  input >> count;

  for (qint32 i = 0; i < count; ++i) {
    input >> pos >> size;
    size.x *= 2;
    size.y *= 2;
    pos.x = pos.x - size.x / 2;
    pos.y = pos.y - size.y / 2;
    level->AppendGround(new Ground(level, pos.x, pos.y,
                                   size.x, size.y));
  }
  file.close();

  return level;
}

void LevelLoader::WriteLevel(Level *level) {
  QFile file(file_name_);
  if(!file.open(QIODevice::WriteOnly)) {
    qDebug() << "LevelLoader::WriteLevel: File can't be opened for writing!\n";
    return;
  }
  QDataStream output(&file);
  // serialize level into the file
  output << level;
  file.close();
}

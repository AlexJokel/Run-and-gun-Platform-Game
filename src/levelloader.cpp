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

const QString& LevelLoader::GetFileName() const {
  return file_name_;
}

Level* LevelLoader::LoadLevel(class Game* game,
                              qreal width, qreal height) const {
  QFile file(file_name_);
  if(!file.open(QIODevice::ReadOnly)) {
    qCritical() << "LevelLoader::LoadLevel: File " << file_name_
                << " can't be opened for reading!\n";
    return nullptr;
  }
  auto level = new Level(game, width, height);
  QDataStream input(&file);
  // read level from the file
  b2Vec2 pos, size;

  input >> pos >> size;
  level->SetPlayer(new Player(level, {pos.x, pos.y},
                              PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
  qint32 count;
  input >> count;

  for (qint32 i = 0; i < count; ++i) {
    input >> pos >> size;
    size.x *= 2;
    size.y *= 2;
    pos.x = pos.x - size.x / 2;
    pos.y = pos.y - size.y / 2;
    level->AppendGround(new Ground(level, {pos.x, pos.y},
                      {size.x, size.y}));
  }
  file.close();

  return level;
}

void LevelLoader::WriteLevel(Level *level) const {
  QFile file(file_name_);
  if(!file.open(QIODevice::WriteOnly)) {
    qCritical() << "LevelLoader::WriteLevel: File " << file_name_
                << " can't be opened for writing!\n";
    return;
  }
  QDataStream output(&file);
  // serialize level into the file
  output << level;
  file.close();
}

QMap<qint32, bool> LevelLoader::LoadState() const {
  QFile file(file_name_);
  if(!file.open(QIODevice::ReadOnly)) {
    qCritical() << "LevelLoader::LoadState: File " << file_name_
                << " can't be opened for reading!\n";
    return QMap<qint32, bool>();
  }
  QDataStream input(&file);
  QMap<qint32, bool> state;
  input >> state;
  file.close();
  return state;
}

void LevelLoader::SaveState(const QMap<qint32, bool>& state) const {
  QFile file(file_name_);
  if(!file.open(QIODevice::WriteOnly)) {
    qCritical() << "LevelLoader::SaveState: File " << file_name_
                << " can't be opened for writing!\n";
    return;
  }
  QDataStream output(&file);
  output << state;
  file.close();
}

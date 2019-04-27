#include <QDebug>

#include "levelloader.h"
#include "staticenemy.h"
#include "roamingenemy.h"

QDataStream& operator<<(QDataStream& out, const b2Vec2& pair) {
  return out << pair.x << pair.y;
}

QDataStream& operator>>(QDataStream& in, b2Vec2& pair) {
  return in >> pair.x >> pair.y;
}

QDataStream& operator<<(QDataStream& out,
                        Object* object) {
  out << object->GetPos() << object->GetSize();
  /// Write borders if object is RoamingEnemy

  if (object->Type() == ObjectType::kRoamingEnemy) {
    out << dynamic_cast<RoamingEnemy*>(object)->GetBorders();
  }
  return out;
}

QDataStream& operator<<(QDataStream& out, Level* level) {
  /// 1) Write Player
  out << level->GetPlayer();

  /// 2) Write Ground
  auto ground = level->GetGround();
  out << ground.size();
  for (const auto& item : ground) {
    out << item;
  }

  /// 3) Write Enemies
  auto enemies = level->GetEnemies();
  out << enemies.size();
  for (const auto& item : enemies) {
    /// Enemy type
    out << static_cast<qint32>(item->Type());
    /// Enemy itself
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

  /// 1) Read Player
  input >> pos >> size;
  level->SetPlayer(new Player(level, {pos.x, pos.y},
                              PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));

  /// 2) Read Ground
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

  /// 3) Read Enemies
  input >> count;

  ObjectType type;
  qint32 type_int;
  b2Vec2 borders;
  for (qint32 i = 0; i < count; ++i) {
    input >> type_int;
    type = static_cast<ObjectType>(type_int);
    input >> pos >> size;
    if (type == ObjectType::kRoamingEnemy) {
      input >> borders;
      /// (horizontal_speed = 2) may also be serialized later
      level->AppendEnemy(new RoamingEnemy(level, {pos.x, pos.y},
        {borders.x, borders.y}, 2, PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
    } else {
      level->AppendEnemy(new StaticEnemy(level, {pos.x, pos.y},
                      PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
    }
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

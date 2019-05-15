#include <QDebug>
#include <QtGlobal>

#include "levelloader.h"
#include "staticenemy.h"
#include "roamingenemy.h"
#include "finishpoint.h"

QDataStream& operator<<(QDataStream& out, const b2Vec2& pair) {
  return out << pair.x << pair.y;
}

QDataStream& operator>>(QDataStream& in, b2Vec2& pair) {
  return in >> pair.x >> pair.y;
}

QDataStream& operator<<(QDataStream& out,
                        Object* object) {
  out << static_cast<qint32>(object->Type());
  out << object->GetPos() << object->GetSize();
  /// Write borders if object is RoamingEnemy
  if (object->Type() == ObjectType::kRoamingEnemy) {
    out << dynamic_cast<RoamingEnemy*>(object)->GetBorders();
  }
  return out;
}

QDataStream& operator<<(QDataStream& out, Level* level) {
  out << level->GetProvidedArrowCount();
  /// 1) Write Player
  out << level->GetPlayer();

  /// 2) Write Ground
  auto grounds = level->GetGround();
  for (const auto& ground : grounds) {
    out << ground;
  }

  /// 3) Write Enemies
  auto enemies = level->GetEnemies();
  for (const auto& enemy : enemies) {
    out << enemy;
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

Level* LevelLoader::LoadLevel(class Game* game) const {
  QFile file(file_name_);
  if(!file.open(QIODevice::ReadOnly)) {
    qCritical() << "LevelLoader::LoadLevel: File " << file_name_
                << " can't be opened for reading!\n";
    return nullptr;
  }
  QDataStream input(&file);
  qint32 provided_level_count;
  input >> provided_level_count;
  auto level = new Level(game, provided_level_count);

  BoundingBox bounding_rect =
    {{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()},
    {std::numeric_limits<float>::min(), std::numeric_limits<float>::min()}};

  ObjectType type;
  qint32 raw_type;
  b2Vec2 pos, size, borders;
  while(!input.atEnd()) {
    input >> raw_type;
    type = static_cast<ObjectType>(raw_type);
    input >> pos >> size;

    switch(type) {
    case ObjectType::kPlayer:
      level->SetPlayer(new Player(level, {pos.x, pos.y},
                                  PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
      UpdateBoundingRect(bounding_rect, {pos.x, pos.y}, {size.x, size.y});
      break;
    case ObjectType::kGround:
    case ObjectType::kFinishPoint:
      size.x *= 2;
      size.y *= 2;
      pos.x = pos.x - size.x / 2;
      pos.y = pos.y - size.y / 2;
      switch (type) {
        case ObjectType::kGround:
          level->AppendGround(new Ground(level, {pos.x, pos.y},
                                         {size.x, size.y}));
          break;
        case ObjectType::kFinishPoint:
          level->AppendGround(new FinishPoint(level, {pos.x, pos.y},
                                              {size.x, size.y}));
          break;
        default:
          break;
      }
      UpdateBoundingRect(bounding_rect, {pos.x, pos.y}, {size.x, size.y});
      break;
    case ObjectType::kStaticEnemy:
      level->AppendEnemy(new StaticEnemy(level, {pos.x, pos.y},
                      PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
      UpdateBoundingRect(bounding_rect, {pos.x, pos.y}, {size.x, size.y});
      break;
    case ObjectType::kRoamingEnemy:
      input >> borders;
      /// (horizontal_speed = 2) may also be serialized later
      level->AppendEnemy(new RoamingEnemy(level, {pos.x, pos.y},
        {borders.x, borders.y}, 2, PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));
      UpdateBoundingRect(bounding_rect, {pos.x, pos.y}, {size.x, size.y});
      break;
    default:
      qCritical() << "Serialized level is damaged!";
    }
  }
  level->setSceneRect({level->MetersToPixels(bounding_rect.top_left),
                      level->MetersToPixels(bounding_rect.bottom_right)});

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

void LevelLoader::UpdateBoundingRect(BoundingBox& box, const b2Vec2& position,
                                     const b2Vec2& size) const {
  box.top_left.x = qMin(box.top_left.x, position.x);
  box.top_left.y = qMin(box.top_left.y, position.y);
  box.bottom_right.x = qMax(box.bottom_right.x, position.x + size.x);
  box.bottom_right.y = qMax(box.bottom_right.y, position.y + size.y);
}

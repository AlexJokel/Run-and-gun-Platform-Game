#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QString>
#include <QDataStream>

#include "level.h"

QDataStream& operator<<(QDataStream& out, const b2Vec2&);
QDataStream& operator>>(QDataStream& in, b2Vec2&);

QDataStream& operator<<(QDataStream& out, Object*);
QDataStream& operator<<(QDataStream& out, Level*);

class LevelLoader {
public:
  LevelLoader(const QString& file_name = "");

  void SetFileName(const QString& new_file_name);
  const QString& GetFileName() const;

  /// Protocol of storing levels in files:
  /// First: qint32 - provided_arrow_count
  /// Then: Just a list of serialized object in any order
  /// Serialized object:
  /// (type, pos, size, *borders*)
  /// *borders* is optional for RoamingEnemy
  Level* LoadLevel(class Game*) const;
  void WriteLevel(Level* level) const;

  QMap<qint32, bool> LoadState() const;
  void SaveState(const QMap<qint32, bool>& state) const;

private:
  struct BoundingBox {
    b2Vec2 top_left;
    b2Vec2 bottom_right;
  };
  void UpdateBoundingRect(BoundingBox& box, const b2Vec2& position,
                          const b2Vec2& size) const;

  QString file_name_;
};

#endif // LEVELLOADER_H

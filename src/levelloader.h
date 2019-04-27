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
  /// 1) Serialized Player : coordinates (4 floats)
  /// 2) Serialized qint32 - number of grounds
  /// 3) List of serialized Ground (4 floats)
  Level* LoadLevel(class Game*, qreal width, qreal height) const;
  void WriteLevel(Level* level) const;

  QMap<qint32, bool> LoadState() const;
  void SaveState(const QMap<qint32, bool>& state) const;

private:
  QString file_name_;
};

#endif // LEVELLOADER_H

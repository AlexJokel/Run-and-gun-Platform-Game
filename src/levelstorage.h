#ifndef LEVELSTORAGE_H
#define LEVELSTORAGE_H

#include <QMap>

#include "levelloader.h"
#include "level.h"

class LevelStorage {
public:
  LevelStorage(qint32 level_number);

  void UnlockLevel(qint32 index);
  void LockLevel(qint32 index);

  Level* GetLevelByIndex(Game* game, qint32 index);

private:
  qint32 level_number_;
  QMap<qint32, bool> open_state_;
  QMap<qint32, Level*> storage_;
  LevelLoader* loader;

  const QString level_path_prefix_ = ":/levels/levels/";
};

#endif // LEVELSTORAGE_H

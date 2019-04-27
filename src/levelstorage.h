#ifndef LEVELSTORAGE_H
#define LEVELSTORAGE_H

#include <QMap>

#include "levelloader.h"
#include "level.h"

class LevelStorage {
public:
  LevelStorage(qint32 level_number);
  ~LevelStorage();

  void UnlockLevel(qint32 index);
  void LockLevel(qint32 index);

  Level* GetLevelByIndex(Game* game, qint32 index);

private:
  const QString kLevelPathPrefix_ = ":/levels/levels/";
  /// inside build folder
  const QString kOpenStatePath_ = "open_levels_state.dat";

  qint32 level_number_;
  QMap<qint32, bool> open_state_;
  QMap<qint32, Level*> storage_;
  LevelLoader* state_loader_;
};

#endif // LEVELSTORAGE_H

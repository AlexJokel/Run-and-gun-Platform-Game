#include "levelstorage.h"

LevelStorage::LevelStorage(qint32 level_number) :
      level_number_(level_number),
      loader (new LevelLoader()) {
  assert(level_number > 0);
  /// open initial levels
  /// later state would be upload from file
  for (qint32 i = 0; i < level_number_; ++i) {
    open_state_[i] = false;
  }
  open_state_[0] = true;
  open_state_[1] = true;
}

void LevelStorage::UnlockLevel(qint32 index) {
  assert(0 <= index && index < level_number_);
  open_state_[index] = true;
}

void LevelStorage::LockLevel(qint32 index) {
   assert(0 <= index && index < level_number_);
  open_state_[index] = false;
}

Level* LevelStorage::GetLevelByIndex(Game* game, qint32 index) {
  assert(0 <= index && index < level_number_);
  if (!open_state_[index]) {
    return nullptr;
  }
  QString file_name = level_path_prefix_ + "level"
      + QString::number(index) + ".dat";
  loader->SetFileName(file_name);
  return loader->LoadLevel(game, 1920, 1080);
}

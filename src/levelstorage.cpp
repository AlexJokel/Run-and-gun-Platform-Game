#include "levelstorage.h"

LevelStorage::LevelStorage(qint32 level_number) :
      level_number_(level_number),
      state_loader_(new LevelLoader(kOpenStatePath_)) {
  assert(level_number > 0);
  /// load open_state_ from file
  open_state_ = state_loader_->LoadState();
}

LevelStorage::~LevelStorage() {
  state_loader_->SaveState(open_state_);
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
  QString file_name = kLevelPathPrefix_ + "level"
      + QString::number(index) + ".dat";
  auto loader = new LevelLoader(file_name);
  return loader->LoadLevel(game, 1920, 1080);
}

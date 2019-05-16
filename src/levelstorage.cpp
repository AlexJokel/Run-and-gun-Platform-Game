#include <QDebug>

#include "fileinitializationhelper.h"
#include "levelstorage.h"

LevelStorage::LevelStorage(qint32 level_number) :
      level_number_(level_number) {
  assert(level_number > 0);

  /// Create defult open state file
  /// if no one is provided
  QFile file(kOpenStatePath_);
  if (!file.exists()) {
    qCritical() << "Initial level state file was created!\n";
    FileInitializationHelper::CreateOpenLevelMap(kOpenStatePath_);
  }
  state_loader_ = new LevelLoader(kOpenStatePath_);
  /// load open_state_ from file
  open_state_ = state_loader_->LoadState();
}

LevelStorage::~LevelStorage() {
  delete state_loader_;
}

void LevelStorage::UnlockLevel(qint32 index) {
  if (0 <= index && index < level_number_) {
   open_state_[index] = true;
    Update();
  }
}

void LevelStorage::LockLevel(qint32 index) {
  if (0 <= index && index < level_number_) {
    open_state_[index] = false;
    Update();
  }
}

void LevelStorage::SaveState() const {
  state_loader_->SaveState(open_state_);
}

void LevelStorage::Update() {
  SaveState();
  emit Changed();
}

bool LevelStorage::IsOpen(qint32 index) const {
  if (index < 0 || index >= level_number_) {
    return false;
  }
  return open_state_.value(index);
}

Level* LevelStorage::GetLevelByIndex(Game* game, qint32 index) const {
  if (index < 0 || index >= level_number_) {
    return nullptr;
  }
  if (!open_state_[index]) {
    return nullptr;
  }
  QString file_name = kLevelPathPrefix_ + "level"
      + QString::number(index) + ".dat";

  auto loader = new LevelLoader(file_name);
  auto level = loader->LoadLevel(game);
  delete loader;
  QObject::connect(level, &Level::Finish, [this, index]() {
    // 'this' in lambdas is const-qualified
    const_cast<LevelStorage*>(this)->UnlockLevel(
        qMin(level_number_, index + 1));
  });
  return level;
}

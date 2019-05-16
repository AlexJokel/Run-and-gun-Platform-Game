#include "settingsloader.h"
#include "soundeffectstorage.h"

SettingsLoader::SettingsLoader(Game* game, const QString &file_name) : game_(game) {
  LevelLoader();
  SetFileName(file_name);
}

void SettingsLoader::LoadSettings() const {
  qDebug() << "Load was called" << endl;
  QFile file(file_name_);
  if(!file.open(QIODevice::ReadOnly)) {
    qCritical() << "LevelLoader::LoadSettings: File " << file_name_
                << " can't be opened for reading!\n";
    return;
  }

  QDataStream input(&file);
  QString field;
  qint32 par;
  while(!input.atEnd()) {
    input >> field;
    input >> par;
    if (field == "Left" || field == "Right" || field == "Jump") {
      Player::controls_map_[field] = static_cast<Qt::Key>(par);
    } else if (field == "Screen") {
      if(par) {
      game_->SetFullScreenMode();
      qDebug() << "was in screen";
      };
    } else if (field == "Music") {
      qDebug() << "was in music";
      game_->SetMusicVolume(par);
    } else if (field == "Effect") {
      qDebug() << "was in effect";
      SoundEffectStorage::SetSoundVolume(par);
    }
  }
  game_->SetFullScreenMode();
  file.close();
}

void SettingsLoader::SaveSettings() const {
  qDebug() << "Save was called!";
  QFile file(file_name_);
  QDataStream output(&file);
  if(!file.open(QIODevice::WriteOnly)) {
    qCritical() << "LevelLoader::SaveSettings: File " << file_name_
                << " can't be opened for writing!\n";
    return;
  }
  for(const auto& key : Player::controls_map_.keys()) {
    output << key << static_cast<qint32>(Player::controls_map_[key]);
  }
  output << "Screen" << static_cast<qint32>(game_->IsFullScreen());
  output << "Music" << game_->GetMusicVolume();
  output << "Effect" << SoundEffectStorage::GetSoundVolume();
  file.close();
}


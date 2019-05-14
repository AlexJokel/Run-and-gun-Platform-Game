#include "soundeffectstorage.h"

int SoundEffectStorage::volume_ = 100;

void SoundEffectStorage::Play(const QString& name) {
  auto player = new QMediaPlayer();
  player->setMedia(QUrl("qrc:/sounds/sounds/" + name + ".mp3"));
  player->setVolume(volume_);
  QObject::connect(player, &QMediaPlayer::mediaStatusChanged,
                   [player](QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::MediaStatus::EndOfMedia) {
      delete player;
    }
  });
  player->play();
}

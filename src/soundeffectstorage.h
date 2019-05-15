#ifndef SOUNDEFFECTSTORAGE_H
#define SOUNDEFFECTSTORAGE_H

#include <QObject>
#include <QMediaPlayer>

class SoundEffectStorage : public QObject {
  Q_OBJECT
public:
  /// Creates a QMediaPlayer to play a sound.
  /// Parameter string is the file name without extension.
  static void Play(const QString&);

public slots:
  static void SetSoundVolume(int new_volume);
  static int GetSoundVolume();

private:
  SoundEffectStorage();

  static int volume_;
};

#endif // SOUNDEFFECTSTORAGE_H

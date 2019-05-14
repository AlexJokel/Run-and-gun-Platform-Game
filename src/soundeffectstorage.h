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

private:
  SoundEffectStorage();

  static int volume_;
};

#endif // SOUNDEFFECTSTORAGE_H

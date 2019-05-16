#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QStack>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "scene.h"

class Game : public QGraphicsView {
  Q_OBJECT
public:
  Game(QApplication*);

  const int default_volume_ = 70;

public slots:
  void PushScene(Scene*);
  void PopScene();

  void InstallScrollDisabler();
  void RemoveScrollDisabler();

  void ChangeScreenState();
  bool IsFullScreen();
  void SetFullScreenMode();
  void RemoveFullScreenMode();

  void SetMusicVolume(int new_volume);
  int GetMusicVolume();

protected:
  QApplication* application_;

  QStack<Scene*> scenes_;

  bool full_screen_;

  class ScrollDisabler : public QObject {
  protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
  };

  ScrollDisabler* scroll_disabler_;

  struct BackgroundMusic {
    QMediaPlayer* player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    ~BackgroundMusic();
  };
  BackgroundMusic background_music_;
};

#endif // GAME_H

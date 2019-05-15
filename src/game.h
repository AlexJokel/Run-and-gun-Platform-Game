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

public slots:
  void PushScene(Scene*);
  void PopScene();

  void InstallScrollDisabler();
  void RemoveScrollDisabler();

  bool IsFullScreen();
  void ChangeScreenState();

protected:
  QApplication* application_;

  QStack<Scene*> scenes_;

  class ScrollDisabler : public QObject {
  protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
  };

  bool full_screen_;
  ScrollDisabler* scroll_disabler_;

  struct BackgroundMusic {
    QMediaPlayer* player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    ~BackgroundMusic();
  };
  BackgroundMusic background_music_;
};

#endif // GAME_H

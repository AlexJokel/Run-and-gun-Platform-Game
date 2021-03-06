#ifndef PICKLEVELMENU_H
#define PICKLEVELMENU_H

#include "menu.h"
#include "level.h"
#include "levelstorage.h"
#include "levelgenerator.h"

class PickLevelMenu : public Menu {
  Q_OBJECT
public:
  PickLevelMenu(class Game*, qreal width, qreal height, QColor color,
                qint32 column_count, qint32 row_count);
  ~PickLevelMenu() override;

public slots:
  void Draw();

protected:
  int column_count_;
  int row_count_;

  QPushButton* back_button_;
  QPushButton* play_random_button_;
  LevelStorage* storage_;
  LevelGenerator* level_generator_;
};

#endif // PICKLEVELMENU_H

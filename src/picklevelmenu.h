#ifndef PICKLEVELMENU_H
#define PICKLEVELMENU_H

#include "menu.h"
#include "level.h"
#include "levelstorage.h"

class PickLevelMenu : public Menu {
public:
  PickLevelMenu(class Game*, qreal width, qreal height, QColor color,
                qint32 num_columns, qint32 num_rows);
protected:
  QVector<Level*> levels_;
  LevelStorage* storage_;
};

#endif // PICKLEVELMENU_H

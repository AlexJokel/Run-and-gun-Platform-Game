#ifndef PICKLEVELMENU_H
#define PICKLEVELMENU_H

#include "menu.h"

class PickLevelMenu : public Menu {
public:
  PickLevelMenu(class Game*, qreal width, qreal height, QColor);
};

#endif // PICKLEVELMENU_H

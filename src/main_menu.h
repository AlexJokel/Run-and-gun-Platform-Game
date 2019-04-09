#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "menu.h"

class MainMenu : public Menu {
public:
  MainMenu(class Game*, qreal width, qreal height, QColor);
private:
  const QColor kPickLevelMenuColor;
};

#endif // MAIN_MENU_H

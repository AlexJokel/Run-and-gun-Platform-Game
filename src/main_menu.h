#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QVBoxLayout>

#include "menu.h"

class MainMenu : public Menu {
public:
  MainMenu(class Game*, qreal width, qreal height, QColor color);
};

#endif // MAIN_MENU_H

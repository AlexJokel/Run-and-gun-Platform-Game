#include "menu.h"

Menu::Menu(class Game* game, qreal width, qreal height, QColor color) : Scene(game, width, height)
{
    setBackgroundBrush(color);
}

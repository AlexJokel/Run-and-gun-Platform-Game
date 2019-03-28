#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "button.h"
#include <list>

class Menu : public Scene {
public:
    Menu(class Game*, qreal width, qreal height, QColor);

protected:
    QString title_text_;
    std::list<Button*> buttons_;
};

#endif // MENU_H

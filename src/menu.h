#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "button.h"
#include <QList>

class Menu : public Scene {
public:
  Menu(class Game*, qreal width, qreal height, QColor);

  const static QColor kGreenDefaultBackground_;

protected:
  QGraphicsTextItem* title_text_;
  QList<Button*> buttons_;
};

#endif // MENU_H

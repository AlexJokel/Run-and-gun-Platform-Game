#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "button.h"
#include <QList>

class Menu : public Scene {
public:
  Menu(class Game*, qreal scene_width, qreal scene_height, QColor color);

  void MoveMenuBlock(qint32 x, qint32 y);

  const static QColor kOrangeDefaultBackground_;

protected:
  QGraphicsTextItem* title_text_;
  /// Subclasses should specify QLayout manager
  /// And fill menu_button_block_ with buttons in constuctor
  QWidget* menu_button_block_;
};

#endif // MENU_H

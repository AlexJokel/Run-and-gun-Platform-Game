#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "button.h"
#include <QList>

class Menu : public Scene {
public:
  Menu(class Game*, qreal width, qreal height, QColor);

  const static QColor kGreenDefaultBackground_;

  /// It is used for accessing scene's widgets
  QList<QGraphicsProxyWidget*> GetProxyWidgetList();

protected:
  QGraphicsTextItem* title_text_;
  /// "The QGraphicsProxyWidget class provides a proxy layer
  /// for embedding a QWidget in a QGraphicsScene"
  QList<QGraphicsProxyWidget*> widgets_;
};

#endif // MENU_H

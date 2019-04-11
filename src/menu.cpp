#include "menu.h"

const QColor Menu::kGreenDefaultBackground_ = QColor(0, 250, 190);

Menu::Menu(class Game* game, qreal width, qreal height, QColor color)
    : Scene(game, width, height) {
  setBackgroundBrush(color);
}

QList<QGraphicsProxyWidget*> Menu::GetProxyWidgetList() {
  return widgets_;
}

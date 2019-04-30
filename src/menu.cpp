#include "menu.h"

const QColor Menu::kOrangeDefaultBackground_ = QColor(255, 213, 0);

Menu::Menu(class Game* game, qreal scene_width, qreal scene_height, QColor color)
     : Scene(game, scene_width, scene_height) {
  setBackgroundBrush(color);
  menu_button_block_ = new QWidget();
  menu_button_block_->setPalette(Qt::transparent);
}

void Menu::MoveMenuBlock(qint32 x, qint32 y) {
  menu_button_block_->move(x, y);
}

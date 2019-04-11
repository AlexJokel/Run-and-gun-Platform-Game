#include <QGridLayout>
#include <QtMath>
#include <QDebug>

#include "cssstylestorage.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"

PickLevelMenu::PickLevelMenu(class Game* game, qreal width, qreal height,
                             QColor color, qint32 num_columns, qint32 num_rows)
    : Menu(game, width, height, color) {
  auto layout = new QGridLayout();
  /// writing hint
  title_text_ = new QGraphicsTextItem("Pick a level");
  title_text_->setFont(QFont("Times", 50));
  title_text_->setPos(this->width() / 2
                      - title_text_->boundingRect().width() / 2, 170);
  addItem(title_text_);

  for (qint32 i = 0; i < num_columns; ++i) {
    for (qint32 j = 0; j < num_rows; ++j) {
      auto button = new Button("Level #" + QString::number(i * num_rows + j), 120, 120);
      button->setStyleSheet
          (CssStyleStorage::GetInstance().GetMenuButtonStyle());
      layout->addWidget(button, i, j);
      QObject::connect(button, &Button::clicked, this, [&] {
         Game()->PushScene(new Level(Game(), 1920, 1080));
      });
    }
  }

  menu_button_block_->setLayout(layout);
  MoveMenuBlock(480, 350);
  addWidget(menu_button_block_);
}

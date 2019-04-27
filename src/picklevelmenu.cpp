#include <QGridLayout>
#include <QtMath>
#include <QDebug>

#include "cssstylestorage.h"
#include "levelloader.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"

PickLevelMenu::PickLevelMenu(class Game* game, qreal width, qreal height,
                             QColor color, qint32 num_columns, qint32 num_rows)
    : Menu(game, width, height, color),
      storage_(new LevelStorage(num_columns * num_rows)) {
  auto layout = new QGridLayout();
  /// writing hint
  title_text_ = new QGraphicsTextItem("Pick a level");
  title_text_->setFont(QFont("Times", 50));
  title_text_->setPos(this->width() / 2
                      - title_text_->boundingRect().width() / 2, 170);
  addItem(title_text_);

  for (int i = 0; i < num_columns; ++i) {
    for (int j = 0; j < num_rows; ++j) {
      auto level_index = i * num_rows + j;
      auto button = new Button("Level #" + QString::number(level_index + 1), 120, 120);

      if (storage_->IsOpen(level_index)) {
        button->setStyleSheet
           (CssStyleStorage::GetInstance().GetMenuButtonStyle());
      } else {
        button->setStyleSheet
           (CssStyleStorage::GetInstance().GetLockedButtonStyle());
      }
      layout->addWidget(button, i, j);
      QObject::connect(button, &Button::clicked, this, [&, level_index] {
        //qDebug() << i << ' ' << j << "\n";
        /// level could be nullptr if either
        /// there is no input file provided or it is locked
        auto level = storage_->GetLevelByIndex(Game(), level_index);
        if (level != nullptr) {
          Game()->PushScene(level);
        }
      });
    }
  }

  menu_button_block_->setLayout(layout);
  MoveMenuBlock(480, 350);
  addWidget(menu_button_block_);
}

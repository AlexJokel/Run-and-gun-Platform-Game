#include <QGridLayout>
#include <QtMath>
#include <QDebug>
#include <QtAlgorithms>

#include "cssstylestorage.h"
#include "levelloader.h"
#include "picklevelmenu.h"
#include "game.h"
#include "level.h"

PickLevelMenu::PickLevelMenu(class Game* game, qreal width, qreal height,
                             QColor color,
                             qint32 column_count, qint32 row_count)
    : Menu(game, width, height, color),
      column_count_(column_count),
      row_count_(row_count),
      storage_(new LevelStorage(column_count * row_count)) {
  /// writing hint
  title_text_ = new QGraphicsTextItem("Pick a level");
  title_text_->setFont(QFont("Times", 50));
  title_text_->setPos(this->width() / 2
                      - title_text_->boundingRect().width() / 2, 0);
  addItem(title_text_);

  Draw();

  QObject::connect(storage_, &LevelStorage::Changed,
                   this, &PickLevelMenu::Draw);

  addWidget(menu_button_block_);
}

void PickLevelMenu::Draw() {
  auto layout = new QGridLayout();
  for (int i = 0; i < column_count_; ++i) {
    for (int j = 0; j < row_count_; ++j) {
      auto level_index = i * row_count_ + j;
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
  if (menu_button_block_->layout() != nullptr) {
    qDeleteAll(menu_button_block_->layout()->children());
    delete menu_button_block_->layout();
  }
  menu_button_block_->setLayout(layout);
  MoveMenuBlock(180, 200);
}

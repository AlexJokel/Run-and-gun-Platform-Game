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
      storage_(new LevelStorage(column_count * row_count)),
      level_generator_(new LevelGenerator()) {
  /// writing hint
  title_text_ = new QGraphicsTextItem("Pick a level");
  QFont title_font("Verdana", 80);
  title_font.setBold(true);
  title_text_->setFont(title_font);
  title_text_->setPos(this->width() / 2
                      - title_text_->boundingRect().width() / 2, 20);
  addItem(title_text_);

  Draw();

  play_random_button_ = new Button("Generate random level", 400, 100);
  play_random_button_->move(450, 430);
  addWidget(play_random_button_);
  play_random_button_->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(play_random_button_, &Button::clicked, this, [&] {
    Game()->PushScene(level_generator_->GenerateRandomLevel(Game(), 30));
  });

  back_button_ = new Button("Back to main menu", 400, 100);
  back_button_->move(450, 550);
  addWidget(back_button_);
  back_button_->setStyleSheet
      (CssStyleStorage::GetInstance().GetMenuButtonStyle());
  QObject::connect(back_button_, &Button::clicked, Game(),
                  &Game::PopScene);
  QObject::connect(storage_, &LevelStorage::Changed,
                   this, &PickLevelMenu::Draw);

  addWidget(menu_button_block_);
}

PickLevelMenu::~PickLevelMenu() {
  delete storage_;
}

void PickLevelMenu::Draw() {
  auto layout = new QGridLayout();
  for (int i = 0; i < column_count_; ++i) {
    for (int j = 0; j < row_count_; ++j) {
      auto level_index = i * row_count_ + j;
      auto button = new Button(
          "Level #" + QString::number(level_index), 150, 150);

      if (storage_->IsOpen(level_index)) {
        button->setStyleSheet
           (CssStyleStorage::GetInstance().GetMenuButtonStyle());
      } else {
        button->setStyleSheet
           (CssStyleStorage::GetInstance().GetLockedButtonStyle());
      }
      button->setFixedSize({250, 180});
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
  MoveMenuBlock(130, 200);
}

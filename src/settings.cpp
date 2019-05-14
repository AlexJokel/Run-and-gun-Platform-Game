#include "settings.h"
#include "main_menu.h"
#include "game.h"
#include "player.h"
#include "level.h"
#include "scene.h"
#include "settings_button.h"
#include "picklevelmenu.h"
#include "cssstylestorage.h"

#include <QScrollBar>

Settings::Settings(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
    auto layout = new QVBoxLayout();

    // creating a title
    title_text_ = new QGraphicsTextItem("SETTINGS");
    title_text_->setFont(QFont("Comic", 70));
    title_text_->setPos(this->width() / 2 -
                        title_text_->boundingRect().width() / 2, 0);
    addItem(title_text_);

    // creating controls buttons
    AddButtonToLayout(layout, "A", 200, 100, "Left");
    AddButtonToLayout(layout, "D", 200, 100, "Right");
    AddButtonToLayout(layout, "Space", 200, 100, "Jump");

    menu_button_block_->setLayout(layout);
    MoveMenuBlock(900, 150);
    addWidget(menu_button_block_);

}

void Settings::AddText(QString text, qreal width, qreal height, QFont font, QColor color) {

}

void Settings::AddButtonToLayout(QVBoxLayout* layout, QString name, qint32 width,
                                 qint32 height, QString key) {
    auto button = new SettingsButton(name, width, height, key);
    button->setStyleSheet
        (CssStyleStorage::GetInstance().GetMenuButtonStyle());
    layout->addWidget(button);
}

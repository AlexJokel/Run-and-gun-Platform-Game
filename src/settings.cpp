#include "settings.h"
#include "main_menu.h"
#include "game.h"
#include "player.h"
#include "level.h"
#include "scene.h"
#include "settings_button.h"

Settings::Settings(class Game* game, qreal width, qreal height, QColor color)
    : Menu(game, width, height, color) {
    //creating a title/*
//    title_text_ = new QGraphicsTextItem(QString("Settings"));
//    QFont titleFont("times new roman", this->width()/50);
//    title_text_->setFont(titleFont);
//    int txPos = this->width() / 2 - title_text_->boundingRect().width() / 2;
//    int tyPos = this->height()/6;
//    title_text_->setPos(txPos, tyPos);
//    addItem(title_text_);

//    //creating quit button
//    Button* quit_button_ = new Button(QString("Back to start menu"));
//    int xPos = this->width()/4.5-quit_button_->boundingRect().width() / 2;
//    int yPos = this->height() -quit_button_->boundingRect().height() * 5;
//    quit_button_->setPos(xPos,yPos);
//    QObject::connect(quit_button_, &Button::clicked, this->Game(),
//                     [this]{Game()->PushScene(new MainMenu(this->Game(), 1920, 1080, Qt::lightGray));});
//    addItem(quit_button_);
//    buttons_.push_back(quit_button_);

//    // creating text for controls buttons
//    QVector<QString> vec = {"Left", "Right", "Shoot", "Exit", "Full screen", "Resolution"};
//    QFont font("arial", this->width()/80);
//    for (int i = 0; i < vec.size(); ++i) {
//        AddText(vec[i], this->width()/3, this->height()/4 + i * this->height()/15, font, Qt::white);
//    }

//    //creating buttons for controls
//    qreal h = this->height()/4;
//    h = AddButton(static_cast<QString>(Player::controls_map_["Left"]), 4 * this->width()/7, this->height()/4);
//    h = AddButton(static_cast<QString>(Player::controls_map_["Right"]), 4 * this->width()/7, h+this->height()/15);

    //creating button for full screen*/
}

void Settings::AddText(QString text, qreal width, qreal height, QFont font, QColor color) {
//    QGraphicsTextItem* text_ = new QGraphicsTextItem(text);
//    text_->setPos(width, height);
//    text_->setFont(font);
//    text_->setDefaultTextColor(color);
//    addItem(text_);
}

qreal Settings::AddButton(QString name, qreal width, qreal height) {
//    Button* button = new Button(QString(name));
//    button->setPos(width, height);
//    addItem(button);
//    buttons_.push_back(button);
//    return height;
}
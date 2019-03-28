#include "button.h"
#include <QGraphicsTextItem>
Button::Button(QString name, QGraphicsItem* parent) : QGraphicsRectItem (parent) {
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);
    setBrush(brush);

    text_ = new QGraphicsTextItem(name, this);
    int xPos = rect().width() / 2 - text_->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - text_->boundingRect().height() / 2;
    text_->setPos(xPos, yPos);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);
    setBrush(brush);
}

void Button::clicked() {}


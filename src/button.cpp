#include "button.h"
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem* parent)
    : QGraphicsRectItem (parent) {
  setRect(0,0,200,50);
  setBrush(Qt::cyan);

  text_ = new QGraphicsTextItem(name, this);
  int xPos = rect().width() / 2 - text_->boundingRect().width() / 2;
  int yPos = rect().height() / 2 - text_->boundingRect().height() / 2;
  text_->setPos(xPos, yPos);

  setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  setBrush(Qt::darkCyan);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  setBrush(Qt::cyan);
}

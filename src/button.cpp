#include "button.h"

Button::Button(QString name, QGraphicsItem* parent)
    : QGraphicsRectItem (parent) {
  setRect(0,0,200,50);
  setBrush(Qt::cyan);

  text_ = new QGraphicsTextItem(name, this);
  auto text_x = rect().width() / 2 - text_->boundingRect().width() / 2;
  auto text_y = rect().height() / 2 - text_->boundingRect().height() / 2;
  text_->setPos(text_x, text_y);

  setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent*) {
  emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
  setBrush(Qt::darkCyan);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
  setBrush(Qt::cyan);
}

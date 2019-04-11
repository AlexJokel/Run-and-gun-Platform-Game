#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button : public QPushButton {
public:
  Button(const QString& title, const QSize& size = {400, 50},
         QWidget* parent = nullptr);
};

#endif // BUTTON_H

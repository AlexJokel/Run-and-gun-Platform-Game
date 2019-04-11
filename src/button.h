#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button : public QPushButton {
public:
  Button(const QString& title, qint32 width, qint32 height,
         QWidget* parent = nullptr);
};

#endif // BUTTON_H

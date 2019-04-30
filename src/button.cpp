#include "button.h"

#include <QRect>

Button::Button(const QString& title, qint32 width, qint32 height,
               QWidget* parent)
    : QPushButton(title, parent) {
  setMinimumWidth(width);
  setMinimumHeight(height);
}

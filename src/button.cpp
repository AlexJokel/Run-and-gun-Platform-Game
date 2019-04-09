#include "button.h"

#include <QRect>

Button::Button(const QString& title, const QSize& size,
               QWidget* parent)
    : QPushButton(title, parent) {
  resize(size);
}

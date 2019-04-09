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
protected:
  virtual void enterEvent(QEvent*) {
    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
  }

  virtual void leaveEvent(QEvent*) {
    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
  }
};

#endif // BUTTON_H

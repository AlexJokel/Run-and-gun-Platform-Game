#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button : public QObject, public QGraphicsRectItem {
  Q_OBJECT
public:
  Button(QString name, QGraphicsItem* parent = nullptr);

  void mousePressEvent(QGraphicsSceneMouseEvent*) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

signals:
  void clicked();

private:
  QGraphicsTextItem* text_;
};

#endif // BUTTON_H

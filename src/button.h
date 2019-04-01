#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Button : public QObject, public QGraphicsRectItem {
  Q_OBJECT
public:
  Button(QString name, QGraphicsItem* parent = nullptr);

  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

signals:
  void clicked();

private:
  QGraphicsTextItem* text_;
};

#endif // BUTTON_H

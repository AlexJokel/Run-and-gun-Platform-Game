#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include "physicalbody.h"

class Object : public QGraphicsRectItem {
public:
  Object(QGraphicsItem* parent = nullptr);

protected:
  PhysicalBody body_;
};

#endif // OBJECT_H

#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include "physicalbody.h"

class Object : public QGraphicsRectItem {
public:
  Object();

private:
  PhysicalBody body_;
};

#endif // OBJECT_H

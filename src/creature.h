#ifndef CREATURE_H
#define CREATURE_H

#include "object.h"

class Creature : public Object {
public:
  Creature(QGraphicsItem* parent = nullptr);
};

#endif // CREATURE_H

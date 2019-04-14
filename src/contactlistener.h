#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <QPair>

#include <Box2D/Box2D.h>

#include "object.h"

class ContactListener : public b2ContactListener {
public:
  void BeginContact(b2Contact*) override;

protected:
  bool CheckContactedTypes(QPair<Object*, Object*>*,
                           ObjectType, ObjectType) const;
  bool CheckContactedTypes(QPair<Object*, Object*>*,
                           ObjectType) const;
};

#endif // CONTACTLISTENER_H

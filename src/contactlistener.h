#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>

#include "object.h"

class ContactListener : public b2ContactListener {
public:
  void BeginContact(b2Contact*) override;
  void EndContact(b2Contact*) override;

protected:
  void CollideObjects(b2Contact*);
};

#endif // CONTACTLISTENER_H

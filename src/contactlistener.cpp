#include "contactlistener.h"

void ContactListener::BeginContact(b2Contact* contact) {
  auto object_1 =
    static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto object_2 =
    static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

  object_1->Collide(object_2->Type());
  object_2->Collide(object_1->Type());
}

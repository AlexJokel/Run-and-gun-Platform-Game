#include "contactlistener.h"

#include "player.h"
#include "arrow.h"
#include "level.h"

void ContactListener::BeginContact(b2Contact* contact) {
  auto arrow = CheckContactedTypes<Arrow>(contact);
  if (arrow != nullptr) {
    arrow->Level()->RemoveObject(arrow);
  }
}

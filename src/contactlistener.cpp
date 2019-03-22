#include "contactlistener.h"

#include "player.h"
#include "arrow.h"
#include "scene.h"

void ContactListener::BeginContact(b2Contact* contact) {
  auto arrow = CheckContactedTypes<Arrow>(contact);
  if (arrow != nullptr) {
    arrow->Scene()->RemoveObject(arrow);
  }
}

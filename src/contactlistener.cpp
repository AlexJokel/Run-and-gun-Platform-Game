#include "contactlistener.h"

#include "player.h"
#include "arrow.h"

void ContactListener::EndContact(b2Contact* contact) {
  auto player_arrow = CheckContactedTypes<Player, Arrow>(contact);
  if (player_arrow.first != nullptr) {
    player_arrow.second->SetOutOfPlayer();
  }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold*) {
  auto player_arrow = CheckContactedTypes<Player, Arrow>(contact);
  if (player_arrow.first != nullptr) {
    if (!player_arrow.second->IsOutOfPlayer()) {
      contact->SetEnabled(false);
    }
  }
}

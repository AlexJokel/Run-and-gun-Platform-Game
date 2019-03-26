#include "contactlistener.h"

#include "player.h"
#include "arrow.h"
#include "level.h"
#include "enemy.h"

void ContactListener::BeginContact(b2Contact* contact) {
  auto player_enemy = CheckContactedTypes<Player, Enemy>(contact);
  if (player_enemy.first != nullptr) {
    player_enemy.first->Level()->RemoveObject(player_enemy.first);
    player_enemy.second->Level()->RemoveObject(player_enemy.second);
    return;
  }

  auto arrow_enemy = CheckContactedTypes<Arrow, Enemy>(contact);
  if (arrow_enemy.first != nullptr) {
    arrow_enemy.first->Level()->RemoveObject(arrow_enemy.first);
    arrow_enemy.second->Level()->RemoveObject(arrow_enemy.second);
    return;
  }

  auto arrow = CheckContactedTypes<Arrow>(contact);
  if (arrow != nullptr) {
    arrow->Level()->RemoveObject(arrow);
    return;
  }
}

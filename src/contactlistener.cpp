#include "contactlistener.h"

#include "player.h"
#include "arrow.h"
#include "level.h"
#include "enemy.h"

void ContactListener::BeginContact(b2Contact* contact) {
  QPair<Object*, Object*> contacted_objects = {
    static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData()),
    static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData())};

  /// Check for arrow-anything collision
  if (CheckContactedTypes(&contacted_objects, ObjectType::kArrow)) {
    contacted_objects.first->Level()->RemoveObject(contacted_objects.first);
    if (contacted_objects.second->Type() == ObjectType::kEnemy) {
      contacted_objects.second->Level()->RemoveObject(contacted_objects.second);
    }
    return;
  }

  /// Check for player-enemy collision
  if (CheckContactedTypes(&contacted_objects,
                          ObjectType::kPlayer, ObjectType::kEnemy)) {
    contacted_objects.first->Level()->RemoveObject(contacted_objects.first);
    contacted_objects.second->Level()->RemoveObject(contacted_objects.second);
    return;
  }
}

bool ContactListener::CheckContactedTypes(QPair<Object*, Object*>* objects,
                                          ObjectType type1,
                                          ObjectType type2) const {
  if ((objects->first->Type() == type1) &&
      (objects->second->Type() == type2)) {
    return true;
  }
  if ((objects->first->Type() == type2) &&
      (objects->second->Type() == type1)) {
    qSwap(objects->first, objects->second);
    return true;
  }
  return false;
}

bool ContactListener::CheckContactedTypes(QPair<Object*, Object*>* objects,
                                          ObjectType type) const {
  if (objects->first->Type() == type) {
    return true;
  }
  if (objects->second->Type() == type) {
    qSwap(objects->first, objects->second);
    return true;
  }
  return false;
}

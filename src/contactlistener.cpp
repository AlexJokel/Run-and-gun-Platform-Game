#include "contactlistener.h"

#include "player.h"
#include "arrow.h"
#include "level.h"
#include "enemy.h"

#include <QMap>

void ContactListener::BeginContact(b2Contact* contact) {
  QPair<Object*, Object*> contacted_objects = {
    static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData()),
    static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData())};

  /// Objects of these types get deleted on ANY contact
  const QVector<ObjectType> deleted_on_any_contact_types = {
    ObjectType::kArrow, ObjectType::kBullet
  };
  for (const auto& type : deleted_on_any_contact_types) {
    if (CheckContactedTypes(&contacted_objects, type)) {
      contacted_objects.first->Level()->RemoveObject(contacted_objects.first);
    }
  }

  /// Objects of key types get deleted on contact with a type in a value vector
  const QMap<ObjectType, QVector<ObjectType>> deleted_on_contact_types = {
    {ObjectType::kPlayer, {ObjectType::kBullet, ObjectType::kEnemy}},
    {ObjectType::kEnemy, {ObjectType::kArrow, ObjectType::kPlayer}},
  };
  for (const auto& key_type : deleted_on_contact_types.keys()) {
    for (const auto& value_type : deleted_on_contact_types.value(key_type)) {
      if (CheckContactedTypes(&contacted_objects, key_type, value_type)) {
        contacted_objects.first->Level()->RemoveObject(contacted_objects.first);
      }
    }
  }
}

bool ContactListener::CheckContactedTypes(QPair<Object*, Object*>* objects,
                                          ObjectType type1,
                                          ObjectType type2) const {
  if (objects->first->Inherits(type1) && objects->second->Inherits(type2)) {
    return true;
  }
  if (objects->first->Inherits(type2) && objects->second->Inherits(type1)) {
    qSwap(objects->first, objects->second);
    return true;
  }
  return false;
}

bool ContactListener::CheckContactedTypes(QPair<Object*, Object*>* objects,
                                          ObjectType type) const {
  if (objects->first->Inherits(type)) {
    return true;
  }
  if (objects->second->Inherits(type)) {
    qSwap(objects->first, objects->second);
    return true;
  }
  return false;
}

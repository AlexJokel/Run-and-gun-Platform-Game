#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <QPair>

#include <Box2D/Box2D.h>

#include "object.h"

class ContactListener : public b2ContactListener {
public:
  void BeginContact(b2Contact*) override;
};

template<typename T1, typename T2>
QPair<T1*, T2*> CheckContactedTypes(b2Contact* contact) {
  auto user_data_1 =
      static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto user_data_2 =
      static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());
  auto data_1_T1 = dynamic_cast<T1*>(user_data_1);
  auto data_2_T2 = dynamic_cast<T2*>(user_data_2);
  auto data_1_T2 = dynamic_cast<T2*>(user_data_1);
  auto data_2_T1 = dynamic_cast<T1*>(user_data_2);
  if ((dynamic_cast<T1*>(user_data_1) != nullptr) &&
      (dynamic_cast<T2*>(user_data_2) != nullptr)) {
    return {data_1_T1, data_2_T2};
  }
  if ((dynamic_cast<T2*>(user_data_1) != nullptr) &&
      (dynamic_cast<T1*>(user_data_2) != nullptr)) {
    return {data_2_T1, data_1_T2};
  }
  return {nullptr, nullptr};
}

template<typename T>
T* CheckContactedTypes(b2Contact* contact) {
  return CheckContactedTypes<T, Object>(contact).first;
}

#endif // CONTACTLISTENER_H

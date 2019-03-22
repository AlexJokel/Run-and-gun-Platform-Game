#ifndef PHYSICALBODY_H
#define PHYSICALBODY_H

#include <Box2D/Box2D.h>

struct PhysicalBody {
  b2Body* body;
  b2BodyDef* body_def;
  b2Shape* shape;
  b2FixtureDef* fixture_def;

  ~PhysicalBody();
};

#endif // PHYSICALBODY_H

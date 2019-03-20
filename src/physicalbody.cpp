#include "physicalbody.h"

PhysicalBody::~PhysicalBody() {
  delete body_def;
  delete shape;
  delete fixture_def;
}

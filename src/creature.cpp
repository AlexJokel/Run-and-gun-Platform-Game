#include "creature.h"

Creature::Creature(class Scene* scene,
                   float x, float y,
                   ShapeInit* shape_init,
                   BodyType body_type,
                   float density,
                   QGraphicsItem* parent)
    : Object(scene, x, y, shape_init, body_type, density, parent) {}

#include "ground.h"

Ground::Ground(class Scene* scene,
               float x, float y,
               float width, float height,
               QGraphicsItem* parent)
    : Object(scene,
             BodyInfo{x + width / 2,
                      y + height / 2,
                      PassShapeInfo(ShapeType::kRectangle, width / 2, height / 2),
                      BodyType::kStatic},
             parent) {}

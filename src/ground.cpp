#include "ground.h"

#include <QGraphicsView>

Ground::Ground(class Level* scene,
               b2Vec2 position,
               b2Vec2 size)
    : Object(scene,
             BodyInfo{position + 0.5f * size,
                      PassShapeInfo(ShapeType::kRectangle,
                                    size.x / 2, size.y / 2),
                      BodyType::kStatic}) {
  setBrush(Qt::darkGray);
  setPen(Qt::NoPen);
}

ObjectType Ground::Type() const {
  return ObjectType::kGround;
}

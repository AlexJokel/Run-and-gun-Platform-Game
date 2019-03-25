#include "ground.h"

#include <QGraphicsView>

Ground::Ground(class Level* scene,
               float x, float y,
               float width, float height)
    : Object(scene,
             BodyInfo{x + width / 2,
                      y + height / 2,
                      PassShapeInfo(ShapeType::kRectangle, width / 2, height / 2),
                      BodyType::kStatic}) {
  setBrush(Qt::darkGray);
  setPen(Qt::NoPen);
}

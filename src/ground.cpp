#include "ground.h"
#include "level.h"
#include <QGraphicsView>

Ground::Ground(class Level* scene,
               float x, float y,
               float width, float height)
    : Object(scene,
             BodyInfo{x + width / 2,
                      y + height / 2,
                      PassShapeInfo(ShapeType::kRectangle, width / 2, height / 2),
                      BodyType::kStatic}) {
    /// Set pixmap
    QPixmap pm1(":/images/images/black_wall.jpg");
    QPixmap pm2 = pm1.scaled(static_cast<int>(Level()->MetersToPixels(width)),
                             static_cast<int>(Level()->MetersToPixels(height)),
                             Qt::IgnoreAspectRatio);
    setPixmap(pm2);
    SetPixmap(":/images/images/black_wall.jpg", Qt::IgnoreAspectRatio);
}

#include "creature.h"

#include <QGraphicsView>

Creature::Creature(class Scene* scene,
                   float x, float y,
                   ShapeInit* shape_init,
                   float horizontal_speed,
                   BodyType body_type,
                   float density,
                   QGraphicsItem* parent)
    : Object(scene, x, y, shape_init, body_type, density, parent),
      kHorizontalSpeed(horizontal_speed) {}

void Creature::advance(int phase) {
  if (phase == 0) return;
  Move();
  Draw();
  scene()->views().front()->centerOn(this);
}

void Creature::Draw() {
  /// Get size and position (in Box2D coordinates)
  auto shape = dynamic_cast<b2PolygonShape*>(body_.shape);
  float half_width = qAbs(shape->m_vertices[0].x);
  float half_height = qAbs(shape->m_vertices[0].y);
  float x = body_.body->GetPosition().x;
  float y = body_.body->GetPosition().y;

  /// Convert into scene coordinates & draw
  setRect(Scene::MetersToPixels(x - half_width),
          Scene::MetersToPixels(y - half_height),
          Scene::MetersToPixels(2 * half_width),
          Scene::MetersToPixels(2 * half_height));
}

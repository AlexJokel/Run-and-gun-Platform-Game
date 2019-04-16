#include "object.h"

#include <QDebug>

#include "level.h"

RectangleShapeInfo::RectangleShapeInfo(float half_width,
                                   float half_height)
    : ShapeInfo(),
      half_width_(half_width),
      half_height_(half_height) {}

b2Shape* RectangleShapeInfo::Init() {
  auto polygon_shape = new b2PolygonShape();
  polygon_shape->SetAsBox(half_width_, half_height_);
  return polygon_shape;
}

BodyInfo::BodyInfo(float x, float y, ShapeInfo* shape_info, BodyType body_type)
  : x(x), y(y), shape_info(shape_info), body_type(body_type) {}

Object::Object(class Level* scene,
               BodyInfo body_info) : QGraphicsRectItem(nullptr) {
  b2BodyDef body_def;
  body_def.position.Set(body_info.x, body_info.y);
  body_def.fixedRotation = true;
  switch (body_info.body_type) {
    case BodyType::kStatic : {
      body_def.type = b2_staticBody;
      break;
    }
    case BodyType::kDynamic : {
      body_def.type = b2_dynamicBody;
      break;
    }
    case BodyType::kKinematic : {
      body_def.type = b2_kinematicBody;
      break;
    }
  }

  b2FixtureDef fixture_def;
  fixture_def.shape = body_info.shape_info->Init();
  fixture_def.density = body_info.density;
  fixture_def.friction = 0;
  fixture_def.restitution = 0;

  /// Add object to the scene
  scene->addItem(this);
  body_ = scene->World()->CreateBody(&body_def);
  body_->CreateFixture(&fixture_def);
  body_->SetUserData(this);

  /// Prepare for drawing
  auto rect_shape = dynamic_cast<b2PolygonShape*>(
      body_->GetFixtureList()->GetShape());
  float half_width = qAbs(rect_shape->m_vertices[0].x);
  float half_height = qAbs(rect_shape->m_vertices[0].y);
  setRect(0,
          0,
          Level()->MetersToPixels(2 * half_width),
          Level()->MetersToPixels(2 * half_height));
  setTransformOriginPoint(rect().center());

  Draw();
}

Object::~Object() {
  /// Delete object from the world
  body_->GetWorld()->DestroyBody(body_);

  /// Delete object from the scene
  Level()->removeItem(this);
}

void Object::advance(int phase) {
  if (phase == 0) return;
  if (body_->GetType() == b2_staticBody) return;
  Draw();
}

/// Works only for square objects!
void Object::Draw() {
  /// Set position
  b2Vec2 top_left_corner = body_->GetPosition()
      + dynamic_cast<b2PolygonShape*>(
          body_->GetFixtureList()->GetShape())->m_vertices[0];
  setPos(Level()->MetersToPixels(top_left_corner.x),
          Level()->MetersToPixels(top_left_corner.y));

  /// Deal with rotation
  auto angle = static_cast<qreal>(body_->GetAngle()); /// in radians
  angle *= 180 / M_PI; /// to degress
  angle *= -1; /// to clockwise
  setRotation(angle);
}

Level* Object::Level() const {
  return dynamic_cast<class Level*>(scene());
}

b2Body* Object::GetBody() const {
  return body_;
}

b2Vec2 Object::GetPos() const {
  return body_->GetWorldCenter();
}

b2Vec2 Object::GetSize() const {
  auto rect_shape = dynamic_cast<b2PolygonShape*>(
      body_->GetFixtureList()->GetShape());
  return {qAbs(rect_shape->m_vertices[0].x),
        qAbs(rect_shape->m_vertices[0].y)};
}

#include "object.h"

PolygonShapeInfo::PolygonShapeInfo(float half_width,
                                   float half_height)
    : ShapeInfo(),
      half_width_(half_width),
      half_height_(half_height) {}

b2Shape* PolygonShapeInfo::Init() {
  auto polygon_shape = new b2PolygonShape;
  polygon_shape->SetAsBox(half_width_, half_height_);
  return polygon_shape;
}

BodyInfo::BodyInfo(float x, float y, ShapeInfo* shape_info, BodyType body_type)
  : x(x), y(y), shape_info(shape_info), body_type(body_type) {}

Object::Object(class Scene* scene,
               BodyInfo body_info,
               QGraphicsItem* parent) : QGraphicsRectItem(parent) {
  body_.body = nullptr;

  body_.body_def = new b2BodyDef;
  body_.body_def->position.Set(body_info.x, body_info.y);
  switch (body_info.body_type) {
    case BodyType::kStatic : {
      body_.body_def->type = b2_staticBody;
      break;
    }
    case BodyType::kDynamic : {
      body_.body_def->type = b2_dynamicBody;
      break;
    }
    case BodyType::kKinematic : {
      body_.body_def->type = b2_kinematicBody;
      break;
    }
  }

  body_.shape = body_info.shape_info->Init();

  body_.fixture_def = new b2FixtureDef;
  body_.fixture_def->shape = body_.shape;
  body_.fixture_def->density = body_info.density;

  scene->AddObject(this);

  Draw();
}

Object::~Object() {
  /// Delete body from the world
  body_.body->GetWorld()->DestroyBody(body_.body);
}

/// Works only for square objects!
void Object::Draw() {
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

Scene* Object::Scene() const {
  return dynamic_cast<class Scene*>(scene());
}

void Scene::AddObject(Object* object) {
  addItem(object);
  object->body_.body = world_->CreateBody(object->body_.body_def);
  object->body_.body->CreateFixture(object->body_.fixture_def);
}

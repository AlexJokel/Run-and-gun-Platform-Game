#include "object.h"

PolygonShapeInit::PolygonShapeInit(float half_width,
                                   float half_height)
    : ShapeInit(),
      half_width_(half_width),
      half_height_(half_height) {}

b2Shape* PolygonShapeInit::Init() {
  auto polygon_shape = new b2PolygonShape;
  polygon_shape->SetAsBox(half_width_, half_height_);
  return polygon_shape;
}

Object::Object(class Scene* scene,
               float x, float y,
               ShapeInit* shape_init,
               BodyType body_type,
               float density,
               QGraphicsItem* parent) : QGraphicsRectItem(parent) {
  body_.body = nullptr;

  body_.body_def = new b2BodyDef;
  body_.body_def->position.Set(x, y);
  switch (body_type) {
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

  body_.shape = shape_init->Init();

  body_.fixture_def = new b2FixtureDef;
  body_.fixture_def->shape = body_.shape;
  body_.fixture_def->density = density;

  scene->AddObject(this);
}

Object::~Object() {
  /// Delete body from the world
  body_.body->GetWorld()->DestroyBody(body_.body);
}

Scene* Object::Scene() const {
  return dynamic_cast<class Scene*>(scene());
}

void Scene::AddObject(Object* object) {
  addItem(object);
  object->body_.body = world_->CreateBody(object->body_.body_def);
  object->body_.body->CreateFixture(object->body_.fixture_def);
}

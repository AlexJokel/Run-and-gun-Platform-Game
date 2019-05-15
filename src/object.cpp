#include "object.h"

#include <QDebug>

#include "level.h"

const QHash<ObjectType, ObjectType> Object::parents_{
    {ObjectType::kObject,       ObjectType::kObject},
    {ObjectType::kCreature,     ObjectType::kObject},
    {ObjectType::kGround,       ObjectType::kObject},
    {ObjectType::kArrow,        ObjectType::kObject},
    {ObjectType::kBullet,       ObjectType::kObject},
    {ObjectType::kFinishPoint,  ObjectType::kGround},
    {ObjectType::kPlayer,       ObjectType::kCreature},
    {ObjectType::kEnemy,        ObjectType::kCreature},
    {ObjectType::kStaticEnemy,  ObjectType::kEnemy},
    {ObjectType::kRoamingEnemy, ObjectType::kEnemy},
};

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

BodyInfo::BodyInfo(b2Vec2 position, ShapeInfo* shape_info, BodyType body_type)
  : position(position), shape_info(shape_info), body_type(body_type) {}

uint qHash(ObjectType type) {
  return static_cast<uint>(type);
}

Object::Object(class Level* scene,
               BodyInfo body_info,
               ObjectType type)
    : QGraphicsPixmapItem(nullptr), type_(type) {
  b2BodyDef body_def;
  body_def.position.Set(body_info.position.x, body_info.position.y);
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

  /// Clean up pointers
  delete fixture_def.shape;
  delete body_info.shape_info;

  /// Prepare for drawing
  auto rect_shape = dynamic_cast<b2PolygonShape*>(GetShape());
  auto half_width =
      Level()->MetersToPixels(qAbs(rect_shape->m_vertices[0].x));
  auto half_height =
      Level()->MetersToPixels(qAbs(rect_shape->m_vertices[0].y));
  setTransformOriginPoint(half_width, half_height);
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
      + dynamic_cast<b2PolygonShape*>(GetShape())->m_vertices[0];
  setPos(Level()->MetersToPixels(top_left_corner));

  /// Deal with rotation
  auto angle = static_cast<qreal>(body_->GetAngle()); /// in radians
  angle *= 180 / M_PI; /// to degress
  setRotation(angle);
}

  /// Sets pixmap of an object
void Object::SetPixmap(QString path, Qt::AspectRatioMode aspect_ratio_mode) {
    QPixmap pm(path);
    auto rect_shape = dynamic_cast<b2PolygonShape*>(GetShape());
    float half_width = qAbs(rect_shape->m_vertices[0].x);
    float half_height = qAbs(rect_shape->m_vertices[0].y);
    QPixmap pm_scaled = pm.scaled(
                static_cast<int>(Level()->MetersToPixels(2 * half_width)),
                static_cast<int>(Level()->MetersToPixels(2 * half_height)),
                aspect_ratio_mode);
    setPixmap(pm_scaled);
}

void Object::ReflectPixmap() {
    QMatrix reflect_matrix(-1, 0, 0, 1, 0, 0);
    QTransform tr(reflect_matrix);
    QPixmap pm_transformed = pixmap().transformed(tr);
    setPixmap(pm_transformed);
}

Level* Object::Level() const {
  return dynamic_cast<class Level*>(scene());
}

b2Body* Object::GetBody() const {
  return body_;
}

b2Shape* Object::GetShape() const {
  b2Fixture* result_fixture = body_->GetFixtureList();
  while (result_fixture->GetNext() != nullptr) {
    result_fixture = result_fixture->GetNext();
  }
  return result_fixture->GetShape();
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

ObjectType Object::Type() const {
  return type_;
}

bool Object::Inherits(ObjectType child, ObjectType parent) {
  while (child != parent) {
    if (child == ObjectType::kObject) return false;
    child = parents_[child];
  }
  return true;
}

void Object::Collide(ObjectType, const b2Contact*) {}

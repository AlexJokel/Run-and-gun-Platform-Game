#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include "physicalbody.h"
#include "scene.h"

enum class BodyType {
  kStatic,
  kDynamic,
  kKinematic
};

enum class ShapeType {
  kPolygon
};

class ShapeInit {
public:
  ShapeInit() = default;
  virtual b2Shape* Init() = 0;
  virtual ~ShapeInit() = default;
};

class PolygonShapeInit : public ShapeInit {
public:
  PolygonShapeInit(float half_width, float half_height);
  b2Shape* Init() override;

protected:
  float half_width_;
  float half_height_;
};

template<typename ...Args>
ShapeInit* PassShapeInit(ShapeType shape_type, Args... args) {
  switch (shape_type) {
    case ShapeType::kPolygon : {
      return new PolygonShapeInit(std::forward<Args>(args)...);
    }
  }
  return nullptr;
}

class Object : public QGraphicsRectItem {
public:
  Object(Scene*,
         float x, float y,
         ShapeInit*,
         BodyType,
         float density = 1,
         QGraphicsItem* parent = nullptr);

  ~Object() override;

  Scene* Scene() const;

  friend class Scene;

protected:
  PhysicalBody body_;
};

#endif // OBJECT_H

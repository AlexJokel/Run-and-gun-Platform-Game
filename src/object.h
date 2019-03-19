#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include "physicalbody.h"

enum class BodyType {
  kStatic,
  kDynamic,
  kKinematic
};

enum class ShapeType {
  kPolygon
};

class ShapeInfo {
public:
  ShapeInfo() = default;
  virtual b2Shape* Init() = 0;
  virtual ~ShapeInfo() = default;
};

class PolygonShapeInfo : public ShapeInfo {
public:
  PolygonShapeInfo(float half_width, float half_height);
  b2Shape* Init() override;

protected:
  float half_width_;
  float half_height_;
};

template<typename ...Args>
ShapeInfo* PassShapeInfo(ShapeType shape_type, Args... args) {
  switch (shape_type) {
    case ShapeType::kPolygon : {
      return new PolygonShapeInfo(std::forward<Args>(args)...);
    }
  }
  return nullptr;
}

struct BodyInfo {
  float x;
  float y;
  ShapeInfo* shape_info;
  BodyType body_type;
  float density = 1;

  BodyInfo(float x, float y, ShapeInfo*, BodyType);
};

class Scene;

class Object : public QGraphicsRectItem {
public:
  Object(Scene*,
         BodyInfo body_info,
         QGraphicsItem* parent = nullptr);

  ~Object() override;

  virtual void Draw();

  Scene* Scene() const;
  friend class Scene;

protected:
  PhysicalBody body_;
};

#endif // OBJECT_H

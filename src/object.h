#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>

namespace CollisionMask {
  enum {
    kDefault = 0x0001,
    kPlayer = 0x0002,
    kArrow = 0x0004,
    kEnemy = 0x0008
  };
}

enum class BodyType {
  kStatic,
  kDynamic,
  kKinematic
};

enum class ShapeType {
  kRectangle
};

class ShapeInfo {
public:
  ShapeInfo() = default;
  virtual b2Shape* Init() = 0;
  virtual ~ShapeInfo() = default;
};

class RectangleShapeInfo : public ShapeInfo {
public:
  RectangleShapeInfo(float half_width, float half_height);
  b2Shape* Init() override;

protected:
  float half_width_;
  float half_height_;
};

template<typename ...Args>
ShapeInfo* PassShapeInfo(ShapeType shape_type, Args... args) {
  switch (shape_type) {
    case ShapeType::kRectangle : {
      return new RectangleShapeInfo(std::forward<Args>(args)...);
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

class Level;

class Object : public QGraphicsRectItem {
public:
  Object(Level*,
         BodyInfo body_info);

  ~Object() override;

  void advance(int) override;
  virtual void Draw();

  Level* Level() const;
  friend class Level;

protected:
  b2Body* body_;
};

#endif // OBJECT_H

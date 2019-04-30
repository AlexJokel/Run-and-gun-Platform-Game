#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <Box2D/Box2D.h>
#include <QBrush>
#include <QHash>

namespace CollisionMask {
  enum {
    kDefault = 0x0001,
    kPlayer = 0x0002,
    kArrow = 0x0004,
    kEnemy = 0x0008,
    kBullet = 0x0010,
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
  b2Vec2 position;
  ShapeInfo* shape_info;
  BodyType body_type;
  float density = 1;

  BodyInfo(b2Vec2, ShapeInfo*, BodyType);
};

enum class ObjectType {
  kObject,
  kGround,
  kCreature,
  kPlayer,
  kEnemy,
  kStaticEnemy,
  kRoamingEnemy,
  kArrow,
  kBullet,
};
uint qHash(ObjectType);

class Level;

class Object : public QObject, public QGraphicsPixmapItem {

public:
  Object(Level*,
         BodyInfo body_info,
         ObjectType = ObjectType::kObject);

  ~Object() override;

  void advance(int) override;
  virtual void Draw();

  void SetPixmap(QString path = "", Qt::AspectRatioMode = Qt::IgnoreAspectRatio);
  void ReflectPixmap();

  Level* Level() const;
  friend class Level;

  b2Body* GetBody() const;

  b2Vec2 GetPos() const;
  b2Vec2 GetSize() const;

  ObjectType Type() const;

  // Checks if 'this' inherits parameter type.
  // Simply goes up the inheritance tree.
  bool Inherits(ObjectType) const;

protected:
  const ObjectType type_;

  b2Body* body_;

private:
  // Inheritance tree
  static const QHash<ObjectType, ObjectType> parents_;
};

#endif // OBJECT_H

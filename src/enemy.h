#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

#include <QSet>

class Enemy : public Creature {
public:
  Enemy(class Level*,
        b2Vec2 position,
        float horizontal_speed,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));

  ObjectType Type() const override;

protected:
  class NearestObjectCallback : public b2RayCastCallback {
  public:
    NearestObjectCallback(const QSet<ObjectType>& opaque_types);

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                        const b2Vec2& normal, float fraction) override;

    Object* GetNearestObject() const;

  protected:
    Object* nearest_object_ = nullptr;
    QSet<ObjectType> opaque_types_;
  };

  void Shoot() override;
};

#endif // ENEMY_H

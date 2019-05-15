#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"

#include <QSet>

class Enemy : public Creature {
public:
  Enemy(class Level*,
        b2Vec2 position,
        float horizontal_speed,
        ObjectType = ObjectType::kEnemy,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));
  ~Enemy() override;

protected:
  class NearestObjectCallback : public b2RayCastCallback {
  public:
    NearestObjectCallback(const QVector<ObjectType>& opaque_types);

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                        const b2Vec2& normal, float fraction) override;

    Object* GetNearestObject() const;

  protected:
    Object* nearest_object_ = nullptr;
    QVector<ObjectType> opaque_types_;
  };

  class Shot;
  Shot* shot_;
  void Shoot() override;

  bool player_visible_ = false;
};

class Enemy::Shot : public QObject {
// This macro doesn't work in nested classes
  Q_OBJECT
public slots:
  /// If ready to shoot, then
  /// sets ready_ to false and launches a single-shot timer.
  /// Returns whether the shot was fired.
  bool TryShooting();

  /// Slot for the timer
  void Ready();

protected:
  bool ready_ = true;

  /// Cooldown in msec
  const int kCooldownTime = 1000;
};

#endif // ENEMY_H

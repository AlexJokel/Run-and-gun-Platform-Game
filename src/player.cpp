#include "player.h"

#include <QGraphicsView>
#include <QDebug>

Player::Player(class Scene* scene,
               float x, float y,
               ShapeInit* shape_init,
               float density,
               QGraphicsItem* parent)
    : Creature(scene, x, y, shape_init, BodyType::kDynamic, density, parent) {
  /// Disable rotation
  body_.body->SetFixedRotation(true);

  Draw();
}

void Player::advance(int phase) {
  if (phase == 0) return;
  Move();
  Draw();
  scene()->views().front()->centerOn(this);
}

void Player::Draw() {
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

void Player::Move() {
  b2Vec2 velocity(0, body_.body->GetLinearVelocity().y);
  if (Scene()->KeyPressed(Qt::Key_A)) {
    velocity.x -= kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_D)) {
    velocity.x += kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_Space)) {
    if (qAbs(velocity.y) < 1e-6f) {
      velocity.y -= kVerticalSpeed_;
    }
  }

  body_.body->SetLinearVelocity(velocity);
}

/// Copy-pasted this function
float Player::CalcSpeedForHeight(b2World* world, float height) {
  if ( height <= 0 )
      return 0;

  float t = 1 / 60.0f;
  b2Vec2 stepGravity = t * t * world->GetGravity();

  float a = -0.5f / stepGravity.y;
  float b = 0.5f;
  float c = height;

  float quadraticSolution1 = ( -b - b2Sqrt( b*b - 4*a*c ) ) / (2*a);
  float quadraticSolution2 = ( -b + b2Sqrt( b*b - 4*a*c ) ) / (2*a);

  float v = quadraticSolution1;
  if ( v < 0 )
      v = quadraticSolution2;

  return v * 60.0f;
}

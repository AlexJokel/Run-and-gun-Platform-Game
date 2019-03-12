#include "player.h"

#include <QGraphicsView>
#include <QDebug>

Player::Player(b2World* world, QGraphicsItem* parent)
    : QGraphicsRectItem(parent) {
  /// Define player body
  body_def_ = new b2BodyDef;
  body_def_->type = b2_dynamicBody;
  body_def_->position.Set(3, 3);
  body_shape_ = new b2PolygonShape;
  body_shape_->SetAsBox(0.5f, 0.5f);
  body_fixture_def_ = new b2FixtureDef;
  body_fixture_def_->shape = body_shape_;
  body_fixture_def_->density = 1;

  /// Add body to the world
  body_ = world->CreateBody(body_def_);
  body_->CreateFixture(body_fixture_def_);

  /// Disable rotation
  body_->SetFixedRotation(true);

  Draw();
}

void Player::advance(int phase)
{
  if (phase == 0) return;
  Move();
  Draw();
  scene()->views().front()->centerOn(this);
}

Scene* Player::Scene() const {
  return dynamic_cast<class Scene*>(scene());
}

Player::~Player() {
  /// Delete body from the world
  body_->GetWorld()->DestroyBody(body_);
}

void Player::Draw() {
  /// Get size and position (in Box2D coordinates)
  float32 half_width = qAbs(body_shape_->m_vertices[0].x);
  float32 half_height = qAbs(body_shape_->m_vertices[0].y);
  float32 x = body_->GetPosition().x;
  float32 y = body_->GetPosition().y;

  /// Convert into scene coordinates & draw
  setRect(Scene::MetersToPixels(x - half_width),
          Scene::MetersToPixels(y - half_height),
          Scene::MetersToPixels(2 * half_width),
          Scene::MetersToPixels(2 * half_height));
}

void Player::Move()
{
  b2Vec2 velocity(0, body_->GetLinearVelocity().y);
  if (Scene()->KeyPressed(Qt::Key_A)) {
    velocity.x -= kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_D)) {
    velocity.x += kHorizontalSpeed;
  }
  if (Scene()->KeyPressed(Qt::Key_Space)) {
    if (qAbs(velocity.y) < 1e-6f) {
      velocity.y -= kVerticalSpeed;
    }
  }

  body_->SetLinearVelocity(velocity);
}

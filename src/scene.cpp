#include "scene.h"

#include <QTimer>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

Scene::Scene(b2World* world, qreal x, qreal y, qreal width, qreal height,
             QObject* parent)
    : QGraphicsScene(x, y, width, height, parent), world_(world) {
  /// Player initialization
  objects_.player = new Player(this, 3, 3);

  /// Create floor
  objects_.ground.append(new Ground(this,
                        0,
                        PixelsToMeters(this->height()) - 1,
                        PixelsToMeters(this->width()),
                        1));

  /// Create walls
  objects_.ground.append(new Ground(this,
                         0,
                         0,
                         1,
                         PixelsToMeters(this->height())));
  objects_.ground.append(new Ground(this,
                         PixelsToMeters(this->width()) - 1,
                         0,
                         1,
                         PixelsToMeters(this->height())));

  /// Frame timer initialization & start
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, &QTimer::timeout, this, &Scene::advance);
  frame_timer->start(static_cast<int>(1000 * kTimeStep_));
}

b2World* Scene::World() const {
  return world_;
}

void Scene::advance() {
  /// Advance the world
  world_->Step(static_cast<float>(kTimeStep_), 8, 3);

  /// Delete scheduled objects
  for (const auto& object : objects_for_removal) {
    delete object;
  }
  objects_for_removal.clear();

  /// Advance the scene
  QGraphicsScene::advance();

  /// Repaint the view
  views().front()->viewport()->repaint();
}

void Scene::keyPressEvent(QKeyEvent *event) {
  keys_[event->key()] = true;
}

void Scene::keyReleaseEvent(QKeyEvent *event) {
  keys_[event->key()] = false;
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  if (event->button() != Qt::LeftButton) return;
  new Arrow(this,
            objects_.player->body_->GetPosition().x,
            objects_.player->body_->GetPosition().y,
            PixelsToMeters(event->scenePos().x()),
            PixelsToMeters(event->scenePos().y()));
}

bool Scene::KeyPressed(qint32 key) const {
  return keys_.value(key, false);
}

void Scene::RemoveObject(Object* object) {
  objects_for_removal.insert(object);
}

qreal Scene::MetersToPixels(float meters) const {
  return static_cast<qreal>(meters) * kMetersToPixelsRatio_;
}

float Scene::PixelsToMeters(qreal pixels) const {
  return static_cast<float>(pixels / kMetersToPixelsRatio_);
}

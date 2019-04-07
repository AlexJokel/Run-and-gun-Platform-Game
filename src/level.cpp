#include "level.h"

#include <QTimer>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#include "game.h"
#include "contactlistener.h"

#include "staticenemy.h"
#include "roamingenemy.h"

Level::Level(class Game* game, qreal width, qreal height)
    : Scene(game, width, height),
      world_(new b2World({0, 9.8f})) {
  /// Set custom view update
  Game()->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

  /// World initialization
  world_->SetContactListener(new ContactListener());

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

  /// Enemy initialization
  objects_.enemies.append(new StaticEnemy(this, 7, 3));
  objects_.enemies.append(new RoamingEnemy(this, 10, 3, 8, 12));

  /// Draw dot grid
  for (size_t x = 0; x < this->width(); x += 100) {
    for (size_t y = 0; y < this->height(); y += 100) {
      addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }

  /// Frame timer initialization & start
  auto frame_timer = new QTimer();
  QObject::connect(frame_timer, &QTimer::timeout, this, &Level::advance);
  frame_timer->start(static_cast<int>(1000 * kTimeStep_));
}

Level::~Level() {
  /// Return game view to defaults
  Game()->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

  for (auto& object : this->items()) {
      delete object;
  }
}

b2World* Level::World() const {
  return world_;
}

void Level::advance() {
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

void Level::keyPressEvent(QKeyEvent *event) {
  keys_[event->key()] = true;
}

void Level::keyReleaseEvent(QKeyEvent *event) {
  keys_[event->key()] = false;
}

void Level::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  if (event->button() == Qt::RightButton) Game()->PopScene();
  if (event->button() != Qt::LeftButton) return;
  new Arrow(this,
            objects_.player->body_->GetPosition().x,
            objects_.player->body_->GetPosition().y,
            PixelsToMeters(event->scenePos().x()),
            PixelsToMeters(event->scenePos().y()));
}

bool Level::KeyPressed(qint32 key) const {
  return keys_.value(key, false);
}

void Level::RemoveObject(Object* object) {
  objects_for_removal.insert(object);
}

qreal Level::MetersToPixels(float meters) const {
  return static_cast<qreal>(meters) * kMetersToPixelsRatio_;
}

float Level::PixelsToMeters(qreal pixels) const {
  return static_cast<float>(pixels / kMetersToPixelsRatio_);
}

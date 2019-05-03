#include "level.h"

#include <QTimer>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#include "game.h"
#include "contactlistener.h"

#include "staticenemy.h"
#include "roamingenemy.h"

Level::Level(class Game* game, qint32 provided_arrow_count,
             qreal width, qreal height)
    : Scene(game, width, height),
      world_(new b2World({0, 9.8f})),
      provided_arrow_count_(provided_arrow_count),
      arrow_count_hint_(new QGraphicsTextItem()) {
  /// Set custom view update
  Game()->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

  /// World initialization
  world_->SetContactListener(new ContactListener());

#ifdef QT_DEBUG
  /// Draw dot grid
  for (size_t x = 0; x < this->width(); x += 100) {
    for (size_t y = 0; y < this->height(); y += 100) {
      addItem(new QGraphicsRectItem(x, y, 1, 1));
    }
  }
#endif

  /// Frame timer initialization
  frame_timer_ = new QTimer();
  QObject::connect(frame_timer_, &QTimer::timeout, this, &Level::advance);
  frame_timer_->setInterval(static_cast<int>(1000 * kTimeStep_));

  /// Enable displaying of arrow_count_hint_ box
  QFont font("Times", 20);
  arrow_count_hint_->setFont(QFont("Times", 20));
  arrow_count_hint_->setDefaultTextColor(QColor(50, 0, 200));
  arrow_count_hint_->show();
  addItem(arrow_count_hint_);
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
  if (finish_scheduled_) {
    emit Finish();
    Game()->PopScene();
    return;
  }

  /// Advance the world
  world_->Step(static_cast<float>(kTimeStep_), 8, 3);

  /// Delete scheduled objects
  for (const auto& object : objects_for_removal) {
    if (object->Type() == ObjectType::kPlayer) {
      Game()->PopScene();
      return;
    }
    delete object;
  }
  objects_for_removal.clear();

  /// Advance the scene
  QGraphicsScene::advance();
  mouse_state_.ClearButtons();

  /// Update position of arrow_count_hint_ box
  arrow_count_hint_->setPos(Game()->mapToScene(20, 20));

  /// Repaint the view
  if (!views().empty()) {
    views().front()->viewport()->repaint();
  } else {
    qDebug() << "Level has no game view!\n";
  }
}

void Level::UpdateRemainingArrows(qint32 left) {
  arrow_count_hint_->setPlainText("Arrows left:" +
                                  QString::number(left));
}

void Level::keyPressEvent(QKeyEvent *event) {
  keys_[event->key()] = true;
}

void Level::keyReleaseEvent(QKeyEvent *event) {
  keys_[event->key()] = false;
}

void Level::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  mouse_state_.buttons_pressed.insert(event->button());
}

void Level::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  mouse_state_.buttons_released.insert(event->button());
  if (event->button() == Qt::RightButton) Game()->PopScene();
}

void Level::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  mouse_state_.mouse_position = PixelsToMeters(event->scenePos());
}

bool Level::KeyPressed(qint32 key) const {
  return keys_.value(key, false);
}

b2Vec2 Level::MousePosition() const {
  return mouse_state_.mouse_position;
}

bool Level::ButtonPressed(Qt::MouseButton button) const {
  return mouse_state_.buttons_pressed.contains(button);
}

bool Level::ButtonReleased(Qt::MouseButton button) const {
  return mouse_state_.buttons_released.contains(button);
}

void Level::Pause() {
  frame_timer_->stop();
}

void Level::Unpause() {
  frame_timer_->start();
}

void Level::RemoveObject(Object* object) {
  objects_for_removal.insert(object);
}

void Level::ScheduleFinish() {
  finish_scheduled_ = true;
}

qreal Level::MetersToPixels(float meters) const {
  return static_cast<qreal>(meters) * kMetersToPixelsRatio_;
}

QPointF Level::MetersToPixels(b2Vec2 point) const {
  return {MetersToPixels(point.x), MetersToPixels(point.y)};
}

float Level::PixelsToMeters(qreal pixels) const {
  return static_cast<float>(pixels / kMetersToPixelsRatio_);
}

float Level::Width() const {
  return PixelsToMeters(width());
}

float Level::Height() const {
  return PixelsToMeters(height());
}

Player* Level::GetPlayer() const {
  return objects_.player;
}

const QList<Ground*>& Level::GetGround() const {
  return objects_.ground;
}

const QList<Enemy*>& Level::GetEnemies() const {
  return objects_.enemies;
}

void Level::SetPlayer(Player* player) {
  objects_.player = player;
}

void Level::AppendGround(Ground* ground) {
  objects_.ground.append(ground);
}

void Level::AppendEnemy(Enemy *enemy) {
  objects_.enemies.append(enemy);
}

qint32 Level::GetProvidedArrowCount() const {
  return provided_arrow_count_;
}

b2Vec2 Level::PixelsToMeters(QPointF point) const {
  return {PixelsToMeters(point.x()), PixelsToMeters(point.y())};
}

void Level::MouseState::ClearButtons() {
  buttons_pressed.clear();
  buttons_released.clear();
}

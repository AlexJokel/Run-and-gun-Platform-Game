[1mdiff --git a/resources/levels/level0.dat b/resources/levels/level0.dat[m
[1mindex 66e26d8..631fb10 100644[m
Binary files a/resources/levels/level0.dat and b/resources/levels/level0.dat differ
[1mdiff --git a/src/fileinitializationhelper.cpp b/src/fileinitializationhelper.cpp[m
[1mindex 1e00759..a58494b 100644[m
[1m--- a/src/fileinitializationhelper.cpp[m
[1m+++ b/src/fileinitializationhelper.cpp[m
[36m@@ -2,8 +2,10 @@[m
 [m
 #include "level.h"[m
 #include "levelloader.h"[m
[32m+[m[32m#include "staticenemy.h"[m
[32m+[m[32m#include "roamingenemy.h"[m
 [m
[31m-void FileInitializationHelper:: CreateLevel(class Game* game, const QString& file_name) {[m
[32m+[m[32mvoid FileInitializationHelper:: CreateFirstLevel(class Game* game, const QString& file_name) {[m
   auto level = new Level(game, 1920, 1080);[m
   /// Player initialization[m
   level->SetPlayer(new Player(level, {3, 3}));[m
[36m@@ -18,6 +20,18 @@[m [mvoid FileInitializationHelper:: CreateLevel(class Game* game, const QString& fil[m
   level->AppendGround(new Ground(level,[m
                          {level->PixelsToMeters(level->width()) - 1, 0},[m
                          {1, level->PixelsToMeters(level->height())}));[m
[32m+[m
[32m+[m[32m  /// Enemy initialization[m
[32m+[m[32m  level->AppendEnemy(new StaticEnemy(level, {7, 3}));[m
[32m+[m[32m  level->AppendEnemy(new RoamingEnemy(level, {10, 3}, {8, 12}));[m
[32m+[m
[32m+[m[32m  /// Draw dot grid[m
[32m+[m[32m  for (size_t x = 0; x < level->width(); x += 100) {[m
[32m+[m[32m    for (size_t y = 0; y < level->height(); y += 100) {[m
[32m+[m[32m      level->addItem(new QGraphicsRectItem(x, y, 1, 1));[m
[32m+[m[32m    }[m
[32m+[m[32m  }[m
[32m+[m
   LevelLoader loader(file_name);[m
   loader.WriteLevel(level);[m
   delete level;[m
[36m@@ -29,6 +43,7 @@[m [mvoid FileInitializationHelper::CreateOpenLevelMap(const QString& file_name) {[m
     open_state[i] = false;[m
   }[m
   open_state[0] = true;[m
[32m+[m[32m  open_state[1] = true;[m
 [m
   QFile file(file_name);[m
   file.open(QIODevice::WriteOnly);[m
[1mdiff --git a/src/fileinitializationhelper.h b/src/fileinitializationhelper.h[m
[1mindex a17816f..d560919 100644[m
[1m--- a/src/fileinitializationhelper.h[m
[1m+++ b/src/fileinitializationhelper.h[m
[36m@@ -6,7 +6,9 @@[m
 class FileInitializationHelper {[m
 public:[m
   /// Path is specified relatively to build directory[m
[31m-  static void CreateLevel(class Game* game, const QString& file_name = "level1.dat");[m
[32m+[m[32m  /// After creating of the level don't forget to add it to resouces[m
[32m+[m[32m  static void CreateFirstLevel(class Game* game,[m
[32m+[m[32m                               const QString& file_name = "level0.dat");[m
   static void CreateOpenLevelMap(const QString& file_name = "open_levels_state.dat");[m
 };[m
 [m
[1mdiff --git a/src/level.cpp b/src/level.cpp[m
[1mindex dbdfbb6..704509e 100644[m
[1m--- a/src/level.cpp[m
[1m+++ b/src/level.cpp[m
[36m@@ -128,10 +128,15 @@[m [mfloat Level::PixelsToMeters(qreal pixels) const {[m
 Player* Level::GetPlayer() const {[m
   return objects_.player;[m
 }[m
[32m+[m
 QList<Ground*> Level::GetGround() const {[m
   return objects_.ground;[m
 }[m
 [m
[32m+[m[32mQList<Enemy*> Level::GetEnemies() const {[m
[32m+[m[32m  return objects_.enemies;[m
[32m+[m[32m}[m
[32m+[m
 void Level::SetPlayer(Player* player) {[m
   objects_.player = player;[m
 }[m
[36m@@ -140,6 +145,10 @@[m [mvoid Level::AppendGround(Ground* ground) {[m
   objects_.ground.append(ground);[m
 }[m
 [m
[32m+[m[32mvoid Level::AppendEnemy(Enemy *enemy) {[m
[32m+[m[32m  objects_.enemies.append(enemy);[m
[32m+[m[32m}[m
[32m+[m
 b2Vec2 Level::PixelsToMeters(QPointF point) const {[m
   return {PixelsToMeters(point.x()), PixelsToMeters(point.y())};[m
 }[m
[1mdiff --git a/src/level.h b/src/level.h[m
[1mindex 693c20e..629609c 100644[m
[1m--- a/src/level.h[m
[1m+++ b/src/level.h[m
[36m@@ -41,9 +41,11 @@[m [mpublic:[m
 [m
   Player* GetPlayer() const;[m
   QList<Ground*> GetGround() const;[m
[32m+[m[32m  QList<Enemy*> GetEnemies() const;[m
 [m
   void SetPlayer(Player* player);[m
   void AppendGround(Ground* ground);[m
[32m+[m[32m  void AppendEnemy(Enemy* enemy);[m
 [m
 public slots:[m
   void advance();[m
[1mdiff --git a/src/levelloader.cpp b/src/levelloader.cpp[m
[1mindex 8485fb1..806ce61 100644[m
[1m--- a/src/levelloader.cpp[m
[1m+++ b/src/levelloader.cpp[m
[36m@@ -1,6 +1,8 @@[m
 #include <QDebug>[m
 [m
 #include "levelloader.h"[m
[32m+[m[32m#include "staticenemy.h"[m
[32m+[m[32m#include "roamingenemy.h"[m
 [m
 QDataStream& operator<<(QDataStream& out, const b2Vec2& pair) {[m
   return out << pair.x << pair.y;[m
[36m@@ -12,16 +14,35 @@[m [mQDataStream& operator>>(QDataStream& in, b2Vec2& pair) {[m
 [m
 QDataStream& operator<<(QDataStream& out,[m
                         Object* object) {[m
[31m-    return out << object->GetPos() << object->GetSize();[m
[32m+[m[32m  out << object->GetPos() << object->GetSize();[m
[32m+[m[32m  /// Write borders if object is RoamingEnemy[m
[32m+[m
[32m+[m[32m  if (object->Type() == ObjectType::kRoamingEnemy) {[m
[32m+[m[32m    out << dynamic_cast<RoamingEnemy*>(object)->GetBorders();[m
[32m+[m[32m  }[m
[32m+[m[32m  return out;[m
 }[m
 [m
 QDataStream& operator<<(QDataStream& out, Level* level) {[m
[32m+[m[32m  /// 1) Write Player[m
   out << level->GetPlayer();[m
[32m+[m
[32m+[m[32m  /// 2) Write Ground[m
   auto ground = level->GetGround();[m
   out << ground.size();[m
   for (const auto& item : ground) {[m
     out << item;[m
   }[m
[32m+[m
[32m+[m[32m  /// 3) Write Enemies[m
[32m+[m[32m  auto enemies = level->GetEnemies();[m
[32m+[m[32m  out << enemies.size();[m
[32m+[m[32m  for (const auto& item : enemies) {[m
[32m+[m[32m    /// Enemy type[m
[32m+[m[32m    out << static_cast<qint32>(item->Type());[m
[32m+[m[32m    /// Enemy itself[m
[32m+[m[32m    out << item;[m
[32m+[m[32m  }[m
   return out;[m
 }[m
 [m
[36m@@ -49,12 +70,14 @@[m [mLevel* LevelLoader::LoadLevel(class Game* game,[m
   // read level from the file[m
   b2Vec2 pos, size;[m
 [m
[32m+[m[32m  /// 1) Read Player[m
   input >> pos >> size;[m
   level->SetPlayer(new Player(level, {pos.x, pos.y},[m
                               PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));[m
[32m+[m
[32m+[m[32m  /// 2) Read Ground[m
   qint32 count;[m
   input >> count;[m
[31m-[m
   for (qint32 i = 0; i < count; ++i) {[m
     input >> pos >> size;[m
     size.x *= 2;[m
[36m@@ -64,6 +87,28 @@[m [mLevel* LevelLoader::LoadLevel(class Game* game,[m
     level->AppendGround(new Ground(level, {pos.x, pos.y},[m
                       {size.x, size.y}));[m
   }[m
[32m+[m
[32m+[m[32m  /// 3) Read Enemies[m
[32m+[m[32m  input >> count;[m
[32m+[m
[32m+[m[32m  ObjectType type;[m
[32m+[m[32m  qint32 type_int;[m
[32m+[m[32m  b2Vec2 borders;[m
[32m+[m[32m  for (qint32 i = 0; i < count; ++i) {[m
[32m+[m[32m    input >> type_int;[m
[32m+[m[32m    type = static_cast<ObjectType>(type_int);[m
[32m+[m[32m    input >> pos >> size;[m
[32m+[m[32m    if (type == ObjectType::kRoamingEnemy) {[m
[32m+[m[32m      input >> borders;[m
[32m+[m[32m      /// (horizontal_speed = 2) may also be serialized later[m
[32m+[m[32m      level->AppendEnemy(new RoamingEnemy(level, {pos.x, pos.y},[m
[32m+[m[32m        {borders.x, borders.y}, 2, PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));[m
[32m+[m[32m    } else {[m
[32m+[m[32m      level->AppendEnemy(new StaticEnemy(level, {pos.x, pos.y},[m
[32m+[m[32m                      PassShapeInfo(ShapeType::kRectangle, size.x, size.y)));[m
[32m+[m[32m    }[m
[32m+[m[32m  }[m
[32m+[m
   file.close();[m
 [m
   return level;[m
[1mdiff --git a/src/levelloader.h b/src/levelloader.h[m
[1mindex 0dc7928..af0f971 100644[m
[1m--- a/src/levelloader.h[m
[1m+++ b/src/levelloader.h[m
[36m@@ -20,9 +20,14 @@[m [mpublic:[m
   const QString& GetFileName() const;[m
 [m
   /// Protocol of storing levels in files:[m
[31m-  /// 1) Serialized Player : coordinates (4 floats)[m
[32m+[m[32m  /// 1) Serialized Player[m
   /// 2) Serialized qint32 - number of grounds[m
[31m-  /// 3) List of serialized Ground (4 floats)[m
[32m+[m[32m  /// 3) List of serialized Grounds[m
[32m+[m[32m  /// 4) Serialized qint32 - number of enemies[m
[32m+[m[32m  /// 5) List of serialized Enemies (type + values depending on type)[m
[32m+[m[32m  /// General format of Player, Ground: (pos, size)[m
[32m+[m[32m  /// General format of Enemy: (type, pos, size, *borders*)[m
[32m+[m[32m  /// *borders* is optional for RoamingEnemy[m
   Level* LoadLevel(class Game*, qreal width, qreal height) const;[m
   void WriteLevel(Level* level) const;[m
 [m
[1mdiff --git a/src/object.h b/src/object.h[m
[1mindex 7accd3b..dd4dab0 100644[m
[1m--- a/src/object.h[m
[1m+++ b/src/object.h[m
[36m@@ -66,6 +66,8 @@[m [menum class ObjectType {[m
   kGround,[m
   kPlayer,[m
   kEnemy,[m
[32m+[m[32m  kRoamingEnemy,[m
[32m+[m[32m  kStaticEnemy,[m
   kArrow,[m
   kBullet,[m
 };[m
[1mdiff --git a/src/roamingenemy.cpp b/src/roamingenemy.cpp[m
[1mindex b39b3eb..67dc573 100644[m
[1m--- a/src/roamingenemy.cpp[m
[1m+++ b/src/roamingenemy.cpp[m
[36m@@ -20,6 +20,10 @@[m [mRoamingEnemy::RoamingEnemy(class Level* level,[m
     : Enemy(level, position, horizontal_speed, shape_info),[m
       borders_(borders) {}[m
 [m
[32m+[m[32mObjectType RoamingEnemy::Type() const {[m
[32m+[m[32m  return ObjectType::kRoamingEnemy;[m
[32m+[m[32m}[m
[32m+[m
 void RoamingEnemy::Move() {[m
   /// The product is positive --> direction and position are[m
   /// to the same side --> direction must be changed.[m
[36m@@ -33,3 +37,7 @@[m [mfloat RoamingEnemy::GetDesiredSpeed() const {[m
   if (player_visible_) return 0;[m
   return kHorizontalSpeed_ * direction_;[m
 }[m
[32m+[m
[32m+[m[32mb2Vec2 RoamingEnemy::GetBorders() const {[m
[32m+[m[32m  return {borders_.left, borders_.right};[m
[32m+[m[32m}[m
[1mdiff --git a/src/roamingenemy.h b/src/roamingenemy.h[m
[1mindex 1217d46..f4cbe2f 100644[m
[1m--- a/src/roamingenemy.h[m
[1m+++ b/src/roamingenemy.h[m
[36m@@ -21,6 +21,9 @@[m [mpublic:[m
                Borders borders,[m
                float horizontal_speed = 2,[m
                ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));[m
[32m+[m[32m  ObjectType Type() const override;[m
[32m+[m
[32m+[m[32m  b2Vec2 GetBorders() const;[m
 [m
 protected:[m
   Borders borders_;[m
[1mdiff --git a/src/staticenemy.cpp b/src/staticenemy.cpp[m
[1mindex 8adba2b..721b1f9 100644[m
[1m--- a/src/staticenemy.cpp[m
[1m+++ b/src/staticenemy.cpp[m
[36m@@ -10,6 +10,10 @@[m [mStaticEnemy::StaticEnemy(class Level* level,[m
   direction_change_timer_->start(kDirectionChangeInterval_);[m
 }[m
 [m
[32m+[m[32mObjectType StaticEnemy::Type() const {[m
[32m+[m[32m  return ObjectType::kStaticEnemy;[m
[32m+[m[32m}[m
[32m+[m
 void StaticEnemy::Move() {[m
   if (player_visible_) {[m
     direction_change_timer_->stop();[m
[1mdiff --git a/src/staticenemy.h b/src/staticenemy.h[m
[1mindex 2b71fdc..10ebed2 100644[m
[1m--- a/src/staticenemy.h[m
[1m+++ b/src/staticenemy.h[m
[36m@@ -11,6 +11,7 @@[m [mpublic:[m
   StaticEnemy(class Level*,[m
               b2Vec2 position,[m
               ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.5f));[m
[32m+[m[32m  ObjectType Type() const override;[m
 [m
 protected:[m
   void Move() override;[m

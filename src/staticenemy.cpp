#include "staticenemy.h"

StaticEnemy::StaticEnemy(class Level* level,
                         b2Vec2 position,
                         ShapeInfo* shape_info)
    : Enemy(level, position, 0, shape_info) {}

void StaticEnemy::Move() {}

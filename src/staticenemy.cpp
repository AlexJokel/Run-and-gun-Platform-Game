#include "staticenemy.h"

StaticEnemy::StaticEnemy(class Level* level,
                         float x, float y,
                         ShapeInfo* shape_info)
    : Enemy(level, x, y, 0, shape_info) {}

void StaticEnemy::Move() {}

#ifndef ARROW_H
#define ARROW_H

#include "object.h"

class Arrow : public Object {
public:
  Arrow(class Scene*,
        float x, float y,
        float mouse_x, float mouse_y,
        ShapeInfo* = PassShapeInfo(ShapeType::kRectangle, 0.5f, 0.1f));

  void SetOutOfPlayer();
  bool IsOutOfPlayer() const;

protected:
  const float kSpeed = 10;

  bool out_of_player = false;
};

#endif // ARROW_H

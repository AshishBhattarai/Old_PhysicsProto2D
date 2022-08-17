#pragma once

#include "physics_entity.h"
#include <glm/glm.hpp>

struct Line2D {
  SpringPhysicsEntity pe; // line physics entity
  glm::vec3 color;
  float thickness;
};

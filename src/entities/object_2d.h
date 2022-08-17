#pragma once

#include "physics_entity.h"
#include <glm/glm.hpp>
#include <memory>

struct Object2D {
  std::shared_ptr<PhysicsEntity> physicsEntity;
  glm::vec4 color;
  float rotation;
  float scale;
  int type; // TOOD: Enum
};

#pragma once

#include "physics_system/shapes.h"
#include <glm/glm.hpp>
#include <memory>

struct PhysicsEntity {
  glm::vec2 position;
  glm::vec2 velocity;
  float elasticity; // e=1 elastic, e=0 non-elastic
  std::unique_ptr<physics::Shape> shape;
};

struct SpringPhysicsEntity {
  std::shared_ptr<PhysicsEntity> pe1; // ball1
  std::shared_ptr<PhysicsEntity> pe2; // ball2
  float length;                       // spring length
  float springFactor;                 // must be: dt^2 < 1/K
  float dampingFactor;                // must be: dt < 1/C
};

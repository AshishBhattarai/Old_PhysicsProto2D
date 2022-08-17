#include "world.h"
#include "utils/slogger.h"
#include <algorithm>
#include <glm/glm.hpp>

namespace physics {

bool World::processWallCollision(PhysicsEntity &pe, glm::vec2 projWall, glm::vec2 nwall) {
  const auto toWall = projWall - pe.position;
  const auto *shape = dynamic_cast<Circle *>(pe.shape.get());
  if (shape != nullptr) {
    float radius = shape->radius;
    if (glm::length(toWall) < radius) {
      // bounch by reflecting the velocity through the wall
      glm::vec2 n = nwall; // wall normal
      float vdotn = glm::dot(pe.velocity, n);

      // prevent print sinking into the ground wall
      if (nwall.x == 1.0f || nwall.y == 1.0f)
        pe.position =
            pe.position + (-nwall * ((pe.position + nwall * projWall) - glm::vec2(radius)));

      // only collide objects moving towards the wall not the objects leaving wall
      if (vdotn < 0.0f) {
        // pe.velocity = pe.velocity - 2.0f * n * (glm::dot(pe.velocity, n)); // bouch back non
        // realistic
        pe.velocity = pe.velocity - (1 + pe.elasticity) * n * vdotn;

        return true;
      }
    }
  }
  return false;
}

void World::update(PhysicsEntity &pe) {
  pe.velocity = pe.velocity + glm::vec2(0.0f, 100 * gravity) * dt; // vt(t+dt) = v(t)
  pe.position = pe.position + pe.velocity * dt;                    // q(t+dt) = v(t)*dt

  World::processWallCollision(pe, glm::vec2(pe.position.x, 0.0f), glm::vec2(0.0f, 1.0f));
  World::processWallCollision(pe, glm::vec2(0.0f, pe.position.y), glm::vec2(1.0f, 0.0f));
  World::processWallCollision(pe, glm::vec2(800.0f, pe.position.y), glm::vec2(-1.0f, 0.0f));
  World::processWallCollision(pe, glm::vec2(pe.position.x, 600.0f), glm::vec2(0.0f, -1.0f));
} // namespace physics

void World::update(SpringPhysicsEntity &pe) {
  glm::vec2 relativeVector = pe.pe2->position - pe.pe1->position;
  glm::vec2 n = glm::normalize(relativeVector);
  float d = glm::length(relativeVector);

  glm::vec2 force = -(50000.0f * n * (d - pe.length)); // -K x n x (d-1), should be dt^2 < 1/K
  // if d > l force will contract the sping.

  // affect balls
  glm::vec2 dv = pe.pe2->velocity - pe.pe1->velocity;
  glm::vec2 nv = n * glm::dot(dv, n);
  glm::vec2 damping = 1000.0f * nv * 0.5f; // C = 50, should fe dt < 1/C
  // damping should be less than 1 (perframe) so 1/C cannot be greater than dt

  pe.pe1->velocity -= (force * 0.5f - damping) * 0.001f;
  pe.pe2->velocity += (force * 0.5f - damping) * 0.001f;
}

} // namespace physics

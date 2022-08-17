#include "entities/physics_entity.h"
#include <array>
#include <vector>

namespace physics {
class World {
private:
  constexpr static float dt = 1 / 60.0f;
  constexpr static float gravity = -10.0f;

  bool processWallCollision(PhysicsEntity &pe, glm::vec2 wall, glm::vec2 nwall);

public:
  void update(PhysicsEntity &pe);
  void update(SpringPhysicsEntity &pe);
};
} // namespace physics

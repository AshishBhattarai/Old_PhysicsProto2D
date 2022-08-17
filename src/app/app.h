#pragma once

#include "display.h"
#include "entities/line_2d.h"
#include "entities/object_2d.h"
#include "input.h"
#include "physics_system/world.h"
#include "render_system/camera.h"
#include "render_system/renderer.h"
#include <vector>

namespace app {
class App {
private:
  std::vector<Object2D> objects;
  std::vector<Line2D> lines;

  Display display;
  Input input;
  render_system::Camera camera;
  render_system::Renderer renderer;
  physics::World world;

  [[nodiscard]] bool checkMouseCollision(const Object2D &object);
  [[nodiscard]] render_system::Renderer createRenderer();

public:
  App(int argc, char **argv);
  void run();
};
}; // namespace app

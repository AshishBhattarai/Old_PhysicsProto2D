#include "app.h"
#include "limits"
#include "loaders.h"
#include "physics_system/shapes.h"
#include "render_system/shaders/program.h"
#include "utils/slogger.h"

using namespace render_system;

namespace app {
App::App(int, char **)
    : objects(), display("prototype", glm::ivec2(800, 600)), input(display), camera(),
      renderer(createRenderer()), world() {}

render_system::Renderer App::createRenderer() {
  Image checkerImage, gridImage;
  Buffer obj2DVertex, obj2DFragment, line2DVertex, line2DFragment;
  bool status = Loaders::loadImage(checkerImage, "resources/defaults/checker.bmp");
  status = Loaders::loadImage(gridImage, "resources/defaults/grid.png");
  status = Loaders::loadBinaryFile(obj2DVertex, "shaders/object_2d_vert.spv");
  status = Loaders::loadBinaryFile(obj2DFragment, "shaders/object_2d_frag.spv");
  status = Loaders::loadBinaryFile(line2DVertex, "shaders/line_2d_vert.spv");
  status = Loaders::loadBinaryFile(line2DFragment, "shaders/line_2d_frag.spv");

  // NVRO
  return Renderer({gridImage, checkerImage, &camera,
                   shader::StageCodeMap{{shader::ShaderStage::VERTEX_SHADER, obj2DVertex},
                                        {shader::ShaderStage::FRAGMENT_SHADER, obj2DFragment}},
                   shader::StageCodeMap{{shader::ShaderStage::VERTEX_SHADER, line2DVertex},
                                        {shader::ShaderStage::FRAGMENT_SHADER, line2DFragment}},
                   800, 600, 800 / 600.0f});
} // namespace app

bool App::checkMouseCollision(const Object2D &object) {
  Input::CursorPos cursorPos = input.getLastCursorPos();
  float distance =
      glm::distance(glm::vec2(cursorPos.x, 600.0f - cursorPos.y), object.physicsEntity->position);
  float radius = std::numeric_limits<float>::max();
  const auto *const ptr = dynamic_cast<physics::Circle *>(object.physicsEntity->shape.get());
  if (ptr) {
    radius = ptr->radius;
  }
  return distance <= radius;
}

void App::run() {

  auto p1Pe = std::shared_ptr<PhysicsEntity>(new PhysicsEntity{
      {300.0f, 300.0f}, glm::vec2(-50.0f, 0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  auto p2Pe = std::shared_ptr<PhysicsEntity>(new PhysicsEntity{
      {396.0f, 300.0f}, glm::vec2(50.0f, 0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  objects.push_back({p1Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  objects.push_back({p2Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  lines.push_back({SpringPhysicsEntity{p1Pe, p2Pe, 96.0f, 100.0f, 10.0f}, glm::vec3(2.0f), 1.5f});
  p1Pe = std::shared_ptr<PhysicsEntity>(new PhysicsEntity{
      {300.0f, 200.0f}, glm::vec2(-50.0f, 0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  p2Pe = std::make_shared<PhysicsEntity>(PhysicsEntity{
      {396.0f, 200.0f}, glm::vec2(50.0f, 0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  objects.push_back({p1Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  objects.push_back({p2Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  lines.push_back({SpringPhysicsEntity{p1Pe, p2Pe, 96.0f, 800.0f, 60.0f}, glm::vec3(2.0f), 1.5f});

  glm::vec2 p1(0.0f, 0.0f);
  glm::vec2 p2 = p1;

  input.addKeyCallback(Input::Key::A, [this, &p1, &p2](const Input::KeyEvent keyEvent) {
    if (keyEvent.action == Input::Action::PRESS) {
      const auto &pos = input.getLastCursorPos();
      if (p1 == glm::vec2(0.0f)) {
        p1 = glm::vec2(pos.x, 600.0f - pos.y);
      } else {
        p2 = glm::vec2(pos.x, 600.0f - pos.y);

        const glm::vec2 velocity = glm::vec2((rand() % 200 - 100), (rand() % 200 - 100));
        const float elastic = (rand() % 10) / 10.0f;

        auto p1Pe = std::shared_ptr<PhysicsEntity>(
            new PhysicsEntity{p1, velocity, elastic, std::make_unique<physics::Circle>(12.0f)});
        auto p2Pe = std::shared_ptr<PhysicsEntity>(
            new PhysicsEntity{p2, velocity, elastic, std::make_unique<physics::Circle>(12.0f)});

        objects.push_back({p1Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
        objects.push_back({p2Pe, glm::vec4(1.0f), 0.0f, 12.0f, 1});

        lines.push_back(
            {SpringPhysicsEntity{p1Pe, p2Pe, 96.0f, 100.0f, 20.0f}, glm::vec3(2.0f), 1.5f});

        p2 = p1 = glm::vec2(0.0f);
      }
    }
  });

  bool bt1Pressed = false;
  std::shared_ptr<PhysicsEntity> selectedBall = nullptr;

  input.addMouseButton(Input::MouseButton::ONE, [this, &bt1Pressed, &selectedBall](
                                                    const Input::MouseButtonEvent buttonEvent) {
    if (buttonEvent.action == Input::Action::PRESS) {

      /*
       *const auto &pos = input.getLastCursorPos();
       *const glm::vec2 spos = glm::vec2(pos.x, 600.0f - pos.y);
       *const glm::vec2 velocity = glm::vec2((rand() % 200 - 100), (rand() %
       *200 - 100)); const float elastic = (rand() % 10) / 10.0f;
       *objects.push_back({std::shared_ptr<PhysicsEntity>(new PhysicsEntity{
       *                       spos, velocity, elastic,
       *std::make_unique<physics::Circle>(12.0f)}), glm::vec4(1.0f),
       *0.0f, 12.0f, 1});
       */
      bt1Pressed = true;
    } else if (buttonEvent.action == Input::Action::RELEASE) {
      bt1Pressed = false;
      selectedBall = nullptr;
    }
  });

  // wheel
  // radius = 50
  // center 400, 300
  glm::vec2 center = glm::vec2(400, 300);
  float radius = 50.0f;
  auto cpe = std::shared_ptr<PhysicsEntity>(
      new PhysicsEntity{center, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  objects.push_back({cpe, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  int zeroIndex = -1;

  int angleDiff = 45;
  for (int angle = 0; angle < 360; angle += angleDiff) {
    glm::vec2 pos = glm::vec2(radius * glm::cos(glm::radians(angle + 0.0f)),
                              radius * glm::sin(glm::radians(angle + 0.0f)));
    pos += center;
    auto cpp = std::shared_ptr<PhysicsEntity>(
        new PhysicsEntity{pos, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});

    if (angle != 0) {
      float len = glm::length(objects.back().physicsEntity->position - cpp->position);
      lines.push_back(
          {SpringPhysicsEntity{cpp, objects.back().physicsEntity, len, 10000.0f, 200.0f},
           glm::vec3(2.0f), 1.5f});
    } else {
      zeroIndex = objects.size();
    }
    if (angle == 360 - angleDiff) {
      float len = glm::length(objects[zeroIndex].physicsEntity->position - cpp->position);
      lines.push_back(
          {SpringPhysicsEntity{cpp, objects[zeroIndex].physicsEntity, len, 10000.0f, 200.0f},
           glm::vec3(2.0f), 1.5f});
    }
    objects.push_back({cpp, glm::vec4(1.0f), 0.0f, 12.0f, 1});
    lines.push_back(
        {SpringPhysicsEntity{cpp, cpe, radius, 10000.0f, 200.0f}, glm::vec3(2.0f), 1.5f});
  }

  glm::vec2 pos1 = glm::vec2(100.0f, 300.0f);
  glm::vec2 pos2 = glm::vec2(300.0f, 300.0f);
  glm::vec2 pos3 = glm::vec2(300.0f, 200.0f);
  glm::vec2 pos4 = glm::vec2(100.0f, 200.0f);

  auto bp1 = std::shared_ptr<PhysicsEntity>(
      new PhysicsEntity{pos1, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  auto bp2 = std::shared_ptr<PhysicsEntity>(
      new PhysicsEntity{pos2, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  auto bp3 = std::shared_ptr<PhysicsEntity>(
      new PhysicsEntity{pos3, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});
  auto bp4 = std::shared_ptr<PhysicsEntity>(
      new PhysicsEntity{pos4, glm::vec2(0.0f), 0.0f, std::make_unique<physics::Circle>(12.0f)});

  objects.push_back({bp1, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  objects.push_back({bp2, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  objects.push_back({bp3, glm::vec4(1.0f), 0.0f, 12.0f, 1});
  objects.push_back({bp4, glm::vec4(1.0f), 0.0f, 12.0f, 1});

  lines.push_back({SpringPhysicsEntity{bp1, bp2, glm::length(pos1 - pos2), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});
  lines.push_back({SpringPhysicsEntity{bp1, bp3, glm::length(pos1 - pos3), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});
  lines.push_back({SpringPhysicsEntity{bp1, bp4, glm::length(pos1 - pos4), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});

  lines.push_back({SpringPhysicsEntity{bp2, bp3, glm::length(pos2 - pos3), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});
  lines.push_back({SpringPhysicsEntity{bp2, bp4, glm::length(pos2 - pos4), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});

  lines.push_back({SpringPhysicsEntity{bp3, bp4, glm::length(pos3 - pos4), 10000.0f, 200.0f},
                   glm::vec3(2.0f), 1.5f});

  while (!display.shouldClose()) {
    renderer.preRender();
    for (auto &line : lines) {
      world.update(line.pe);
    }
    for (auto &obj : objects) {
      if (checkMouseCollision(obj)) {
        obj.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        if (!bt1Pressed) selectedBall = obj.physicsEntity;
      } else {
        obj.color = glm::vec4(1.0f);
      }
      world.update(*obj.physicsEntity.get());
    }

    if (selectedBall != nullptr && bt1Pressed) {
      glm::vec2 dir = glm::vec2(input.getLastCursorPos().x, 600.0f - input.getLastCursorPos().y) -
                      selectedBall->position;
      selectedBall->velocity = dir * 10.0f;
    }

    renderer.renderLines(lines);
    renderer.renderObjects(objects);
    input.update();
    display.update();
  }
} // namespace app
} // namespace app

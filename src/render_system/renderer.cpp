#include "renderer.h"
#include "camera.h"
#include "core/image.h"
#include "default_primitives_renderer.h"
#include "mesh.h"
#include "render_defaults.h"
#include "renderable_entity.h"
#include "shaders/general_vs_ubo.h"
#include "utils/slogger.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <limits>

namespace render_system {

Renderer::Renderer(const RendererConfig &config)
    : camera(config.camera), generalVSUBO(), object2DShader(config.object2DCode),
      line2DShader(config.line2DCode) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto &renderDefaults = RenderDefaults::getInstance(&config.gridImage, &config.checkerImage);
  DefaultPrimitivesRenderer::getInstance(&renderDefaults.getCube(), &renderDefaults.getPlane());
  updateProjectionMatrix(config.width, config.height);
}

glm::mat4 Renderer::getTransform(const Object2D &object) {
  return glm::translate(glm::mat4(1.0f), glm::vec3(object.physicsEntity->position, 0.0f)) *
         glm::eulerAngleYXZ(0.0f, object.rotation, 0.0f) * glm::scale(glm::vec3(object.scale));
}

void Renderer::preRender() {
  glClear(GL_COLOR_BUFFER_BIT);
  // TODO: global / gener ubos handled by render_system (data) ??
  generalVSUBO.setViewMatrix(camera->getViewMatrix());
  generalVSUBO.setCameraPos(camera->position);
}

void Renderer::renderObjects(const std::vector<Object2D> &objects) {
  auto &pr = DefaultPrimitivesRenderer::getInstance();
  for (auto &object : objects) {
    const auto &transform = getTransform(object);
    object2DShader.bind();
    object2DShader.loadColor(object.color);
    object2DShader.loadTransformation(transform);
    pr.drawPlane();
  }
}

void Renderer::renderLines(const std::vector<Line2D> &lines) {
  auto &pr = DefaultPrimitivesRenderer::getInstance();
  for (auto &line : lines) {
    line2DShader.bind();
    line2DShader.load(line);
    pr.drawPlane();
  }
}

void Renderer::renderSkybox(const Texture &texture) {
  // render skybox
}

void Renderer::updateProjectionMatrix(float width, float height) {
  projectionMatrix = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
  generalVSUBO.setProjectionMatrix(projectionMatrix);
}

void Renderer::renderGridPlane() {}

} // namespace render_system

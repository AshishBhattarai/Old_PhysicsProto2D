#pragma once

#include "entities/line_2d.h"
#include "entities/object_2d.h"
#include "frame_buffer.h"
#include "render_system/shaders/program.h"
#include "shaders/general_vs_ubo.h"
#include "shaders/line_2d.h"
#include "shaders/object_2d.h"
#include "types.h"
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Buffer;
class Image;
namespace render_system {
struct Mesh;
struct RenderableEntity;
struct PointLight;
struct BaseMaterial;
class Camera;
class Texture;

struct RendererConfig {
  const Image &gridImage;
  const Image &checkerImage; // can be removed after RenderSystem construction

  const Camera *camera;
  const shader::StageCodeMap &object2DCode;
  const shader::StageCodeMap &line2DCode;

  float width;
  float height;
  float ar;
};

class Renderer {
private:
  glm::mat4 projectionMatrix;
  const Camera *camera;
  shader::GeneralVSUBO generalVSUBO;
  shader::Object2d object2DShader;
  shader::Line2d line2DShader;

  glm::mat4 getTransform(const Object2D &object);

public:
  Renderer(const RendererConfig &config);

  void updateProjectionMatrix(float width, float height);
  void setCamera(const Camera *camera) { this->camera = camera; }
  void loadPointLight(const PointLight &pointLight, uint idx);
  void loadPointLightCount(size_t count);
  void preRender();
  /**
   * @brief renderMesh
   * @param dt
   * @param transform
   * @param meshId
   * @param primIdToMatId
   */
  [[nodiscard]] const Camera *getCamera() { return camera; }
  void renderObjects(const std::vector<Object2D> &objects);
  void renderLines(const std::vector<Line2D> &lines);
  void renderSkybox(const Texture &texture);
  void renderGridPlane();

  [[nodiscard]] glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
};
} // namespace render_system

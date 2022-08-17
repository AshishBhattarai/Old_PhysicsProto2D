#include "object_2d.h"
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#define OBJECT_VERTEX_SHADER
#define OBJECT_FRAGMENT_SHADER
#include "glsl/config_2d.h"

namespace render_system::shader {
Object2d::Object2d(const StageCodeMap &codeMap) : Program(codeMap) {
  bind();
  loadColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  loadTransformation(glm::mat4(1.0f));
  unBind();
}

void Object2d::loadTransformation(const glm::mat4 &transform) {
  glUniformMatrix4fv(VERT_U_TRANSFORMATION_LOC, 1, GL_FALSE, glm::value_ptr(transform));
}

void Object2d::loadColor(const glm::vec4 &color) {
  glUniform4fv(FRAG_U_OBJ_COLOR_LOC, 1, glm::value_ptr(color));
}

} // namespace render_system::shader

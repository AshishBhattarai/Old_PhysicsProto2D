#include "line_2d.h"
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LINE_VERTEX_SHADER
#define LINE_FRAGMENT_SHADER
#include "glsl/config_2d.h"

namespace render_system::shader {
Line2d::Line2d(const StageCodeMap &codeMap) : Program(codeMap) {}

void Line2d::load(const Line2D &line) {
  glUniform2fv(FRAG_U_LINE_P1, 1,
               glm::value_ptr(line.pe.pe1->position / glm::vec2(800.0f, 600.0f)));
  glUniform2fv(FRAG_U_LINE_P2, 1,
               glm::value_ptr(line.pe.pe2->position / glm::vec2(800.0f, 600.0f)));
  glUniform3fv(FRAG_U_LINE_COLOR_LOC, 1, glm::value_ptr(line.color));
  glUniform1f(FRAG_U_LINE_THICK_LOC, line.thickness / 1000.0f);
}
} // namespace render_system::shader

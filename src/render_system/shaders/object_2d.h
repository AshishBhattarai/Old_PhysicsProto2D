#pragma once
#include "glm/glm.hpp"
#include "program.h"

namespace render_system::shader {
class Object2d : public Program {
public:
  Object2d(const StageCodeMap &codeMap);

  void loadTransformation(const glm::mat4 &transform);
  void loadColor(const glm::vec4& color);
};

}; // namespace render_system::shader

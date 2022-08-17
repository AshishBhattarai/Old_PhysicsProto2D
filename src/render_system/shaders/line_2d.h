#pragma once
#include "entities/line_2d.h"
#include "glm/glm.hpp"
#include "program.h"

namespace render_system::shader {
class Line2d : public Program {
public:
  Line2d(const StageCodeMap &codeMap);

  void load(const Line2D &line);
};

} // namespace render_system::shader

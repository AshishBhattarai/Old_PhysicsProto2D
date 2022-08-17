#version 460 core
#extension GL_GOOGLE_include_directive : require

#define LINE_VERTEX_SHADER
#include "config_2d.h"

layout(location = VERT_A_POSITION_LOC) in vec2 aPos;

layout(std140, binding = VERT_UB_GENERAL_LOC) uniform GeneralUB {
  mat4 projection;
  mat4 view;
};

layout(location = VERT_INTERFACE_BLOCK_LOC) out VS_OUT {
  vec3 worldPos;
  vec2 uv;
}
vs_out;

void main(void) {
  vec4 pos = vec4(aPos, 0.0f, 1.0f);
  gl_Position = pos;
  vs_out.uv = aPos * 0.5f + 0.5f;
  vs_out.worldPos = pos.xyz;
}

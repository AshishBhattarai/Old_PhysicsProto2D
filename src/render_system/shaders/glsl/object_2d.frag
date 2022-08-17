#version 460 core
#extension GL_GOOGLE_include_directive : require

#define OBJECT_FRAGMENT_SHADER
#include "config_2d.h"

layout(location = COLOR_ATTACHMENT0) out vec4 fragColor;

layout(location = VERT_INTERFACE_BLOCK_LOC) in VS_OUT {
  vec3 worldPos;
  float scale;
  vec2 uv;
}
fs_in;

layout(location = FRAG_U_OBJ_TYPE_LOC) uniform int objType;
layout(location = FRAG_U_OBJ_COLOR_LOC) uniform vec4 color;

void main(void) {
  vec2 worldCoord = fs_in.worldPos.xz;

  vec2 ruv = (fs_in.uv - 0.5f) / 0.5f;
  vec2 cpos = ruv * fs_in.scale;
  float len = length(cpos);

  if (len > fs_in.scale)
    discard;
  else {
    float factor = 1.0f - smoothstep(fs_in.scale - 2.0f, fs_in.scale, len);
    fragColor = color * factor;
  }
}

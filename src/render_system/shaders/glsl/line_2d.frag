#version 460 core
#extension GL_GOOGLE_include_directive : require

#define LINE_FRAGMENT_SHADER
#include "config_2d.h"

layout(location = COLOR_ATTACHMENT0) out vec4 fragColor;

layout(location = VERT_INTERFACE_BLOCK_LOC) in VS_OUT {
  vec3 worldPos;
  vec2 uv;
}
fs_in;

layout(location = FRAG_U_LINE_COLOR_LOC) uniform vec3 color;
layout(location = FRAG_U_LINE_THICK_LOC) uniform float thickness;
layout(location = FRAG_U_LINE_P1) uniform vec2 p1; // normalized p1
layout(location = FRAG_U_LINE_P2) uniform vec2 p2; // normalized p2

float distLine(vec2 a, vec2 b, vec2 p) {
  vec2 ba = b - a;
  vec2 pa = p - a;
  vec2 projPa = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.) * ba; // project pa on ba
  return abs(length(pa - projPa)); // lenght between pa and porject of pa on ba
}

void main(void) {
  vec2 worldCoord = fs_in.worldPos.xz;
  float d = distLine(p1, p2, fs_in.uv);
  if (d > thickness + 0.005f)
    discard;
  else {
    float line = smoothstep(thickness, thickness + 0.005f, d);
    fragColor = mix(vec4(color, 1.0f), vec4(0.0f), line);
  }
}

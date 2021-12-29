#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
  vec4 texColor = texture(uTexture, vFragTexCoords);
  if(texColor.a < 0.1)
    discard;
  fFragColor = texColor;
};
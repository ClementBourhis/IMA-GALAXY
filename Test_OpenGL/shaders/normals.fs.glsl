#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragtexCoords;

out vec3 fFragColor;

void main() {
  fFragColor = normalize(vFragNormal);
  //fFragColor = vec3(1,1,1);
};
#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertextexCoords;

out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragtexCoords;

void main() {
    vFragPosition = aVertexPosition;
    vFragNormal = aVertexNormal;
    vFragtexCoords = aVertextexCoords;

    gl_Position = vec4(aVertexPosition, 1);
};
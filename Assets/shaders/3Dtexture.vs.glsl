#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

//à envoyer au fs
out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

//varaiables uniforme des transfo matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


void main() {
   //coordonées homogènes du vertex
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    //calcul des sorties
    vFragPosition = vec3(uMVMatrix * vertexPosition);
    vFragNormal = vec3(uNormalMatrix * vertexNormal);
    vFragTexCoords = aVertexTexCoords;

    //gl_Position
    gl_Position = uMVPMatrix * vertexPosition;
};
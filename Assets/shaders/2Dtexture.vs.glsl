#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

out vec2 vFragTexCoords;

void main() {
	vFragTexCoords = aVertexTexCoords;
	
	gl_Position = vec4(aVertexPosition.xz, 0, 1);
}

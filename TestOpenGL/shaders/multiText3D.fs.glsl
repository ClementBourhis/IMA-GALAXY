#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

out vec3 fFragColor;

void main() {
    fFragColor = texture(uTexture, vTexture).xyz + texture(uTexture2, vTexture).xyz;
}

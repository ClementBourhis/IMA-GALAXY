#version 330


in vec2 vFragTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    //fFragColor = vec3(1,0,0);
    fFragColor = texture(uTexture, vFragTexCoords).rgb;
}
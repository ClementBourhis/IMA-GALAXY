#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexture;

//matrices de transfo
uniform mat4 uMVPMatrix; //pour l'envoi au GPU (gl_position)
uniform mat4 uMVMatrix; //pour la caméra (out position)
uniform mat4 uNormalMatrix; //pour transformer la normal (out normal)

//sortie pour le fragment shader
out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexture;

void main() {
    //coordonées homogènes du vertex
    vec4 vertexPosition = vec4(aPosition, 1);
    vec4 vertexNormal = vec4(aNormal, 0);

    //calcul des sorties
    vPosition = vec3(uMVMatrix * vertexPosition);
    vNormal = vec3(uNormalMatrix * vertexNormal);
    vTexture = aTexture;

    //gl_Position
    gl_Position = uMVPMatrix * vertexPosition;
}

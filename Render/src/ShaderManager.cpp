#include <Render/ShaderManager.hpp>

ShaderManager::ShaderManager(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile)
    : _vsFile(vsFile), _fsFile(fsFile), _program(glimac::loadProgram(vsFile, fsFile)){
};


void ShaderManager::addUniformVariable(const std::string &name){
    GLint uLocationVariable = glGetUniformLocation(getId(), name.c_str());
    _uVariables.insert(std::pair<std::string, GLint>(name, uLocationVariable));
};

void ShaderManager::sendUniformMatrix4(std::string name, glm::mat4 value){
    glUniformMatrix4fv(_uVariables[name], 1, GL_FALSE, glm::value_ptr(value));
};

void ShaderManager::sendUniformVector3(std::string name, glm::vec3 value){
    glUniform3f(_uVariables[name], value.x, value.y, value.z);
};

void ShaderManager::sendUniformInt(std::string name, int num){
    glUniform1i(_uVariables[name], num);
};


void ShaderManager::use(){
    _program.use();
}
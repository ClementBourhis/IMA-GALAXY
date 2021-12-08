#include <Mesh/Mesh.hpp>

Mesh::Mesh(const std::vector<ShapeVertex> vertices)
    :_vertices(vertices){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, ShaderManager* shader)
    :_vertices(vertices), _shader(shader){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, ShaderManager* shader, Texture* texture)
    :_vertices(vertices), _shader(shader), _texture(texture){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices)
    :_vertices(vertices), _indices(indices){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader)
    :_vertices(vertices), _indices(indices), _shader(shader){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader, Texture* texture)
    :_vertices(vertices), _indices(indices), _shader(shader), _texture(texture){
}


void Mesh::free(){
    _vbo->~VBO();
    _vao->~VAO();
    _texture->free();
}


void Mesh::bind(){
    _vao->bind();
    if(_shader){
        _shader->use();
    }
    if(_texture){
        _texture->bind();
    }
}

void Mesh::debind(){
    if(_texture){
        _texture->debind();
    }
    _vao->debind();
}

void Mesh::fillBuffers(){
    _vbo->fillBuffer(_vertices);
    if(haveIBO()){
        _ibo->fillBuffer(_indices);
        _vao->fillBuffer(_vertices, _vbo, _ibo);
    }
    else{
        _vao->fillBuffer(_vertices, _vbo);
    }
}


void Mesh::draw(){
    if(haveIBO()){
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, nbVertex());
    }
}

void Mesh::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, const glm::mat4 &ViewMatrix){
    _shader->sendUniformMatrix4("uMVPMatrix", ProjMatrix*MVMatrix*ViewMatrix);
    _shader->sendUniformMatrix4("uMVMatrix", MVMatrix*ViewMatrix);
    _shader->sendUniformMatrix4("uNormalMatrix", glm::inverse(MVMatrix));
    _shader->sendUniformInt("uTexture", 0);

    draw();
}
#include <Mesh/Mesh.hpp>

Mesh::Mesh(const std::vector<ShapeVertex> vertices)
    :_vertices(vertices), _isFill(false){
}

Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices)
    :_vertices(vertices), _indices(indices), _isFill(false){
}

/*Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader)
    :_vertices(vertices), _indices(indices), _shader(shader){
}*/

/*Mesh::Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader, Texture* texture)
    :_vertices(vertices), _indices(indices), _shader(shader), _texture(texture){
}*/

/*Mesh::Mesh(ShaderManager* shader, Texture* texture)
    :_shader(shader), _texture(texture){
}*/

void Mesh::free(){
    _vbo->~VBO();
    _vao->~VAO();
}


void Mesh::bind(){
    _vao->bind();
}

void Mesh::debind(){
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
    _isFill = true;
}


void Mesh::draw(){
    if(haveIBO()){
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, nbVertex());
    }
}
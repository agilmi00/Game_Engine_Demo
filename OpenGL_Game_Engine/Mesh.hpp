//
//  Mesh.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <vector>
#include <iostream>


#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "Textura.hpp"

#include "glm/glm.hpp"


struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 textCoords;  
};

class Mesh
{
  
public:
    Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, std::vector<Textura>&& texturas);
    ~Mesh()
    {
        for(uint32_t e = 0; e < _texturas.size(); e++) {
//            glDeleteTextures(1, _texturas[e].getID());
        }
    };
    
    std::vector<Textura> _texturas;
    void render(const uint32_t& shaderProgram,const bool& wireFrame);

private:
    mutable uint32_t VBO;
    mutable uint32_t EBO;
    mutable uint32_t VAO;
    
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
    
    
    void initBuffers() const;
};

#endif /* Mesh_hpp */

//
//  Mesh.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, std::vector<Textura>&& texturas)
{
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    _texturas = std::move(texturas);
    initBuffers();
};

void Mesh::initBuffers() const
{
    
    // (Vertex buffer object)
    glGenBuffers(1, &VBO);
    // (Element buffer object)
    glGenBuffers(1, &EBO);
    // (Vertex array object)
    glGenVertexArrays(1, &VAO);


    // Contains the state of the VBO and EBO buffers.
    glBindVertexArray(VAO);

    // Bind the VBO created to a GL_ARRAY type buffer predefined by OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

    // Bind the EBO created to a GL_ELEMENT_ARRAY_BUFFER type buffer predefined by OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy index data into buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

    // Tells OpenGL how the vertex information is structured
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
  
    // Pointer to the normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
    
    // Pointer to the texture coords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (offsetof(Vertex, textCoords)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
}

void Mesh::render(const uint32_t& shaderProgram,const bool& wireFrame)
{
    
    // Number of textures per type.
    uint32_t diffuseNum  = 0;
    uint32_t normalNum   = 0;
    uint32_t specularNum = 0;
    uint32_t heightNum   = 0;
    std::string numero;
    
//    std::vector<uint32_t> textLoc;
    
    for(uint32_t e = 0; e < _texturas.size(); e++) {

        const auto type = _texturas[e].getTipo();
        if (type == Textura::enumTipo::eDiffuse)
        {
            numero = std::to_string(diffuseNum++);
        }
        else if(type == Textura::enumTipo::eNormal)
        {
            numero = std::to_string(normalNum++);
        }
            
        else if(type == Textura::enumTipo::eSpecular)
        {
            numero = std::to_string(specularNum++);
        }
            
        else if(type == Textura::enumTipo::eHeight)
        {
            numero = std::to_string(heightNum++);
        }
        // Activate the corresponding texture unit
        glActiveTexture(GL_TEXTURE0 + e);
        std::string tex_name = Textura::labelTipo[int(type)]+ numero; // Examp -> textura_normal0

        GLuint textLoc = glGetUniformLocation(shaderProgram, tex_name.c_str());
        glUniform1i(textLoc, e);
        
//        std::cout << _texturas[e].getID();
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, *_texturas[e].getID());
    }

    if (wireFrame)
    {
        // WireFrame Mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        // Normal Mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
   
//    for(uint32_t e = 0; e < _texturas.size(); e++) {
//        
//        // Activate the corresponding texture unit
//        glActiveTexture(GL_TEXTURE0 + e);
//        
//        // Bind the texture
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }
//    
    // Returns to the default texture unit.
    
    
    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindVertexArray(0);

}

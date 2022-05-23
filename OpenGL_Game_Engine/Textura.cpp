//
//  Textura.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda
//

#include "Textura.hpp"
#include "stb_image.h"




const char *Textura::labelTipo[5] = {"textura_diffuse","textura_specular","textura_normal","textura_height","textura_ambient"};

void Textura::cargar(const std::string &nombre, const std::string &directory, enumTipo tipoTextura, bool voltear)
{
    
    _tipo = tipoTextura;
    std::string rutaTextura;
    if (directory != "" &&  nombre != "") {
        rutaTextura = directory + "/" + nombre;
    }
    
    glGenTextures(1, &_id);

    if (voltear)
    {
        stbi_set_flip_vertically_on_load(true);
    }
    

    int width, height, numCanales;
    unsigned char* data = stbi_load((rutaTextura).c_str(), &width, &height, &numCanales, 0);
    if (!data)
    {
        throw std::runtime_error("ERROR: Texture path doesn´t exists -> "+rutaTextura);
    }
    
    GLenum format = GL_RED;
    if (numCanales == 1)
    format = GL_RED;
    else if (numCanales == 3)
    format = GL_RGB;
    else if (numCanales == 4)
    format = GL_RGBA;

    // Gen the texture
    glBindTexture(GL_TEXTURE_2D, _id);
    
    // Config - > texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    //allocate memory on the graphics card for the texture. It's fine if
    //texture_data doesn't have any data in it, the texture will just appear black
    //until you update it.
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
   
//    glDeleteTextures(1, &_id);

//    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}
GLuint* Textura::getID()
{
    return &_id;
}
enum Textura::enumTipo Textura::getTipo() const 
{
    return _tipo;
}

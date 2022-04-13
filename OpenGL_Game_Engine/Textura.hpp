//
//  Textura.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda
//

#ifndef Textura_hpp
#define Textura_hpp

#include <stdio.h>
#include <iostream>

#include "GLFW/glfw3.h"
#include <OpenGL/gl3.h>

#endif /* Textura_hpp */

class Textura {

public:
    enum class enumTipo {
        eDiffuse, eSpecular, eNormal, eHeight, eAmbient
      };
    static const char *labelTipo[5]; // = {"textura_diffuse","texture_normal"};
    
    Textura()
    {
        
    }
    ~Textura()
    {
//        glDeleteTextures(1, &_id);
    }

    GLuint* getID();
    enum enumTipo getTipo() const;
    const std::string getNombre ();

    void cargar(const std::string &nombre, const std::string &directory, enumTipo tipoTextura = enumTipo::eDiffuse, bool voltear=true);
private:
    
    
    GLuint _id;
    enum enumTipo _tipo;
};

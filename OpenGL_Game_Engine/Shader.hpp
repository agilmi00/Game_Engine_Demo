//
//  Shader.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//
#define GL_SILENCE_DEPRECATION
#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader();
    ~Shader(){}
    
    unsigned int setUp(const char* vertexPath, const char* fragmentPath);
    
private:
    unsigned int compile(const char* vertexShaderCode, const char* fragmentShaderCode);
};

#endif /* Shader_hpp */

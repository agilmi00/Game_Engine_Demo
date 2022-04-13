//
//  Shader.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "Shader.hpp"

Shader::Shader(){}

unsigned int Shader::setUp(const char* vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read the files
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::CANNOT_READ" << std::endl;
    }
    return compile(vertexCode.c_str(), fragmentCode.c_str());
    
}

unsigned int Shader::compile(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    unsigned int vertexShader, fragmentShader, shaderProgram;
    
    // Gen a GL_VERTEX_SHADER object type.
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the vertex shader code to it.
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    // Fragment shader
    // This shader calculates the color of the pixels based on the object colors and the scene lights
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    // Create a shaderProgram with the 2 shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR ->" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

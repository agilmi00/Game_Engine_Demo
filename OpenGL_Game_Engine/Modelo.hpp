//
//  Modelo.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef Modelo_hpp
#define Modelo_hpp
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <thread>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "Mesh.hpp"


class Modelo {
    
public:
    Modelo() = default;
    Modelo(std::string& ruta)
    {
        try {
            cargarModelo(ruta);
        }
        catch (std::exception &exception)
        {
            std::cout << exception.what() << std::endl;
        }
        
    }
    ~Modelo()
    {
        
    };
    void draw(unsigned int& shaderProgram, bool& light) {
            for(unsigned int i = 0; i < meshes.size(); i++) {
                meshes[i].render(shaderProgram, light);
        }
    }
    
    void freeVram()
    {
        for (Mesh &mesh : meshes) {
            for (Textura &textura : mesh._texturas) {
                glDeleteTextures(1, textura.getID());
            }
        }
    }
    std::vector<Mesh> getMeshes();
private:
        
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<std::string> texturasCargadas;
    void cargarModelo(const std::string &ruta);
    void procesarNodo(aiNode* nodo, const aiScene* escena);
    Mesh procesarMesh(aiMesh* mesh, const aiScene* escena);
    
    std::vector<Textura> cargarMaterialtexturas(aiMaterial *material, aiTextureType aiTipo, Textura::enumTipo tipoTextura);
};
#endif /* Modelo_hpp */

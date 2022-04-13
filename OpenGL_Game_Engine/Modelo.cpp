//
//  Modelo.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "Modelo.hpp"

// Load the model and save the meshes into a vector.
void Modelo::cargarModelo(std::string const &ruta)
{
    
    // Read the file with ASSIMP
    Assimp::Importer importer;
    const aiScene* escena = importer.ReadFile(ruta, aiProcess_Triangulate /*| aiProcess_GenSmoothNormals*/ | aiProcess_FlipUVs |/* aiProcess_CalcTangentSpace |*/ aiProcess_JoinIdenticalVertices);
    if(!escena || escena->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !escena->mRootNode)
    {
        std::string error;
        error += "Error: Model LOAD -> ";
        error += importer.GetErrorString();
        throw std::runtime_error(error);
    }
    directory = ruta.substr(0, ruta.find_last_of('/'));

    procesarNodo(escena->mRootNode, escena);
}

void Modelo::procesarNodo(aiNode* nodo, const aiScene* escena)
{
    // Procesa las meshes del nodo actual.
    for(uint32_t i = 0; i < nodo->mNumMeshes; i++)
    {
        aiMesh* mesh = escena->mMeshes[nodo->mMeshes[i]];
        meshes.push_back(procesarMesh(mesh, escena));
        
    }
    // Procesa los nodos hijos.
    for(uint32_t i = 0; i < nodo->mNumChildren; i++)
    {
        procesarNodo(nodo->mChildren[i], escena);
    }
}

std::vector<Textura> Modelo::cargarMaterialtexturas(aiMaterial *material, aiTextureType aiTipo, Textura::enumTipo tipoTextura)
{
    
    std::vector<Textura> texturas;
    for(uint32_t i = 0; i < material->GetTextureCount(aiTipo); i++)
    {
        aiString str;
        material->GetTexture(aiTipo, i, &str);
        
        // Check if the texture is already loaded.
        bool repetida = false;
        for(uint32_t j = 0; j < texturasCargadas.size(); j++)
        {
            if(std::strcmp(texturasCargadas[j].data(), str.C_Str()) == 0)
            {
                repetida = true; 
                break;
            }
        }
        if(!repetida)
        {
            
            Textura textura = Textura();
            try {
                textura.cargar(str.C_Str(), this->directory, tipoTextura);
                texturas.push_back(textura);
                texturasCargadas.push_back(str.C_Str());
            }
            catch (std::exception &exception)
            {
                std::cout << exception.what() << std::endl;
            }
        }
    }
    return move(texturas);
}

Mesh Modelo::procesarMesh(aiMesh *mesh, const aiScene *escena)
{
    std::vector<Vertex> vertices;
    std::vector<Textura> texturas;
    std::vector<uint32_t> indices;
    
  
    // Travel the mesh vertex
    for(uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        
        Vertex vertex;
        glm::vec3 vector;
        // pos
        vector.x = mesh->mVertices[i].x; // Copy the vertex position
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;
       // normal
       if (mesh->HasNormals())
       {
           vector.x = mesh->mNormals[i].x;
           vector.y = mesh->mNormals[i].y;
           vector.z = mesh->mNormals[i].z;
           vertex.normal = vector;
       }
       // textCoords
       if(mesh->mTextureCoords[0])
       {
           glm::vec2 vec;
           
           vec.x = mesh->mTextureCoords[0][i].x;
           vec.y = mesh->mTextureCoords[0][i].y;
           vertex.textCoords = vec;
       }
       else
           vertex.textCoords = glm::vec2(0.0f, 0.0f);

       vertices.push_back(vertex);
    }
    // Travel every triangle of the mesh to obtain the 3 index.
    for(uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; j++) {
           
           indices.push_back(face.mIndices[j]);
        }
    }
    
    // Process the textures
    aiMaterial* material = escena->mMaterials[mesh->mMaterialIndex];
    
    // 1. diffuse maps
    std::vector<Textura> diffuseMaps = cargarMaterialtexturas(material, aiTextureType_DIFFUSE, Textura::enumTipo::eDiffuse /*"textura_diffuse"*/);
    texturas.insert(texturas.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Textura> specularMaps = cargarMaterialtexturas(material, aiTextureType_SPECULAR, Textura::enumTipo::eSpecular /*"textura_specular"*/);
    texturas.insert(texturas.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Textura> normalMaps = cargarMaterialtexturas(material, aiTextureType_NORMALS, Textura::enumTipo::eNormal /*"textura_normal"*/);
    texturas.insert(texturas.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Textura> heightMaps = cargarMaterialtexturas(material, aiTextureType_HEIGHT,Textura::enumTipo::eHeight /*"textura_height"*/);
    texturas.insert(texturas.end(), heightMaps.begin(), heightMaps.end());
   
    return Mesh(std::move(vertices), std::move(indices), std::move(texturas));
   }

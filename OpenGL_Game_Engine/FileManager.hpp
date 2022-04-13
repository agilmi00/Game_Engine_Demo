//
//  FileManager.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef FileManager_hpp
#define FileManager_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "ECSManager.hpp"
#include "Vendor/JSON/nlohmann/json.hpp"
#include "TagName.hpp"
#include "TransformComponent.hpp"
#include "Model.hpp"
#include "DirectionalLightComponent.hpp"
#include "PointLightComponent.hpp"
#include "SpotLightComponent.hpp"


using json = nlohmann::ordered_json;
using jsonN = nlohmann::json;

namespace glm
{
    void from_json(const json& j, glm::vec3& vec);
    void to_json(json& j, vec3& vec);
}

class FileManager
{
    
public:
    FileManager(std::unique_ptr<ECSManager> & ECSManager);
    ~FileManager()
    {
        
    }
    
    void init(std::vector<GameObject>& gameObjects)
    {
        _gameObjects = &gameObjects;
    }
    void serialize(const std::string& path);
    bool deserialize(const std::string& path);
    void setECSManager(std::unique_ptr<ECSManager> & ECSManager);
private:
    
    std::vector<GameObject>* _gameObjects;
    ECSManager* _ECSManager;
};

#endif /* FileManager_hpp */

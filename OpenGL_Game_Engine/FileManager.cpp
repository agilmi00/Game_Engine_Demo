//
//  FileManager.cpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#include "FileManager.hpp"

FileManager::FileManager(std::unique_ptr<ECSManager>& ECSManager)
{
    _ECSManager = ECSManager.get();
}
void FileManager::setECSManager(std::unique_ptr<ECSManager>& ECSManager)
{
    _ECSManager = ECSManager.get();
}
void FileManager::serialize(const std::string& path)
{
    json j;
    json jPath;
    std::string object;
    int cont = 0;
    for (GameObject gameObject : *_gameObjects)
    {
        object = "GameObject"+std::to_string(cont);
        j["GameObjects"][object];
        j["GameObjects"][object]["Components"];
        Info info = _ECSManager->getInfoGameObject(gameObject);
        if (info.test(0)) // Tag
        {
            j["GameObjects"][object]["Components"]["TagName"] = &_ECSManager->getComponent<TagName>(gameObject).tagName[0];
        }
        if (info.test(1)) // Transform
        {
            to_json(j["GameObjects"][object]["Components"]["TransformComponent"]["Translation"], _ECSManager->getComponent<TransformComponent>(gameObject).Translation);
            to_json(j["GameObjects"][object]["Components"]["TransformComponent"]["Rotation"], _ECSManager->getComponent<TransformComponent>(gameObject).Rotation);
            to_json(j["GameObjects"][object]["Components"]["TransformComponent"]["RotEuler"], _ECSManager->getComponent<TransformComponent>(gameObject).RotEuler);
            to_json(j["GameObjects"][object]["Components"]["TransformComponent"]["Scale"], _ECSManager->getComponent<TransformComponent>(gameObject).Scale);
        }
        if (info.test(2)) // Model
        {
            j["GameObjects"][object]["Components"]["ModelPath"] = _ECSManager->getComponent<Model>(gameObject).ruta;
        }
        if (info.test(3)) // DirectionalLight
        {
            to_json(j["GameObjects"][object]["Components"]["DirectionalLightComponent"]["Color"], _ECSManager->getComponent<DirectionalLightComponent>(gameObject).lightColor);
            to_json(j["GameObjects"][object]["Components"]["DirectionalLightComponent"]["Direction"], _ECSManager->getComponent<DirectionalLightComponent>(gameObject).lightDirection);
            j["GameObjects"][object]["Components"]["DirectionalLightComponent"]["AmbientIntensity"] = _ECSManager->getComponent<DirectionalLightComponent>(gameObject).ambientIntensity;
            j["GameObjects"][object]["Components"]["DirectionalLightComponent"]["DiffuseIntensity"] = _ECSManager->getComponent<DirectionalLightComponent>(gameObject).diffuseIntensity;
            
        }
        if (info.test(4)) // PointLight
        {
            to_json(j["GameObjects"][object]["Components"]["PointLightComponent"]["Color"], _ECSManager->getComponent<PointLightComponent>(gameObject).lightColor);
            j["GameObjects"][object]["Components"]["PointLightComponent"]["DiffuseIntensity"] = _ECSManager->getComponent<PointLightComponent>(gameObject).diffuseIntensity;
            j["GameObjects"][object]["Components"]["PointLightComponent"]["MaxRadius"] = _ECSManager->getComponent<PointLightComponent>(gameObject).maxRadius;
        }
        if (info.test(5)) // SpotLight
        {
            to_json(j["GameObjects"][object]["Components"]["SpotLightComponent"]["Color"], _ECSManager->getComponent<SpotLightComponent>(gameObject).lightColor);
            j["GameObjects"][object]["Components"]["SpotLightComponent"]["DiffuseIntensity"] = _ECSManager->getComponent<SpotLightComponent>(gameObject).diffuseIntensity;
            j["GameObjects"][object]["Components"]["SpotLightComponent"]["MaxRadius"] = _ECSManager->getComponent<SpotLightComponent>(gameObject).maxRadius;
        }
        if (info.test(6)) // Health
        {
            
        }
        
        cont++;
    }
    std::ofstream o(path);
    o << std::setw(4) << j << std::endl;
}

bool FileManager::deserialize(const std::string &path)
{
    std::ifstream f(path);
    json j;
    f >> j;
    json jPath;
    std::string object;
    int cont = 0;
    if (f)
    {
        if (!j["GameObjects"].empty())
        {
            for (int i = 0; i < j["GameObjects"].size(); i++)
            {   object = "GameObject"+std::to_string(cont);
                
                GameObject gameObject;
                gameObject = _ECSManager->createGameObject();

                _gameObjects->push_back(gameObject);
                
                jPath = j["GameObjects"][object]["Components"];
                
                if (!jPath.empty())
                {
                    
                    if (!jPath["TagName"].empty())
                    {
                        _ECSManager->addComponent(gameObject, TagName{.tagName = jPath["TagName"]});
                    }
                    if (!jPath["TransformComponent"].empty())
                    {
                        _ECSManager->addComponent(gameObject, TransformComponent{});
                        auto& transform = _ECSManager->getComponent<TransformComponent>(gameObject);
                        from_json(jPath["TransformComponent"]["Translation"],transform.Translation);
                        from_json(jPath["TransformComponent"]["Rotation"],transform.Rotation);
//                        from_json(jPath["TransformComponent"]["RotEuler"],transform.RotEuler);
                        from_json(jPath["TransformComponent"]["Scale"],transform.Scale);
                    }
                    if (!jPath["ModelPath"].empty())
                    {
                        std::string ruta = jPath["ModelPath"];
                        _ECSManager->addComponent(gameObject, Model{.modelo = Modelo(ruta)});
                        _ECSManager->getComponent<Model>(gameObject).ruta = ruta;
                        
                    }
                    if (!jPath["DirectionalLightComponent"]["Color"].empty())
                    {
                        _ECSManager->addComponent(gameObject, DirectionalLightComponent{});
                        auto& light = _ECSManager->getComponent<DirectionalLightComponent>(gameObject);
                        // Vec3
                        from_json(jPath["DirectionalLightComponent"]["Color"], light.lightColor);
                        from_json(jPath["DirectionalLightComponent"]["Direction"], light.lightDirection);
                        // Float
                        light.ambientIntensity = jPath["DirectionalLightComponent"]["AmbientIntensity"];
                        light.diffuseIntensity = jPath["DirectionalLightComponent"]["DiffuseIntensity"];
                    }
                    if (!jPath["PointLightComponent"]["Color"].empty())
                    {
                        _ECSManager->addComponent(gameObject, PointLightComponent{});
                        auto& light = _ECSManager->getComponent<PointLightComponent>(gameObject);
                        from_json(jPath["PointLightComponent"]["Color"], light.lightColor);
                        light.diffuseIntensity = jPath["PointLightComponent"]["DiffuseIntensity"];
                        light.maxRadius = jPath["PointLightComponent"]["MaxRadius"];
                    }
                    if (!jPath["SpotLightComponent"]["Color"].empty())
                    {
                        _ECSManager->addComponent(gameObject, SpotLightComponent{});
                        auto& light = _ECSManager->getComponent<SpotLightComponent>(gameObject);
                        from_json(jPath["SpotLightComponent"]["Color"], light.lightColor);
                        light.diffuseIntensity = jPath["SpotLightComponent"]["DiffuseIntensity"];
                        light.maxRadius = jPath["SpotLightComponent"]["MaxRadius"];
                    }
                }
                cont++;
            }
        }
    }
    return true;
}

namespace glm
{
    void from_json(const json& j, vec3& vec)
    {
        j.at("x").get_to(vec.x);
        j.at("y").get_to(vec.y);
        j.at("z").get_to(vec.z);
    }
    void to_json(json& j, vec3& vec)
    {
        j = {{"x", vec.x}, {"y", vec.y}, {"z", vec.z}};
    }
}
namespace mth
{
    void from_json(const json& j, Quatern& quat)
    {
        j.at("x").get_to(quat.x);
        j.at("y").get_to(quat.y);
        j.at("z").get_to(quat.z);
        j.at("w").get_to(quat.w);
    }
    void to_json(json& j, Quatern& quat)
    {
        j = {{"x", quat.x}, {"y", quat.y}, {"z", quat.z}, {"w", quat.w}};
    }
    void from_json(const json& j, Vector3& vec)
    {
        j.at("x").get_to(vec.x);
        j.at("y").get_to(vec.y);
        j.at("z").get_to(vec.z);
    }
    void to_json(json& j, Vector3& vec)
    {
        j = {{"x", vec.x}, {"y", vec.y}, {"z", vec.z}};
    }
}


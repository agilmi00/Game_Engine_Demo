//
//  Render.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef Render_hpp
#define Render_hpp

 
#include <stdio.h>
#include "System.hpp"
#include "Modelo.hpp"
#include "Camera.hpp"
#include "TransformComponent.hpp"
#include "PointLightComponent.hpp"
#include "DirectionalLightComponent.hpp"
#include "Model.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "ECSManager.hpp"



class Render : public System
{
public:
    void init(Camera* camera, uint32_t shaderProgram, std::unique_ptr<ECSManager> & ECSManager)
    {
        _camera = camera;
        _shaderProgram = shaderProgram;
        _ECSManager = ECSManager.get();
        
        DirectionalLightSystem = _ECSManager->newSystem<DirectionalLight>();
        {
            Info info;
            info.set(_ECSManager->getComponentType<DirectionalLightComponent>());
            _ECSManager->setSystemInfo<DirectionalLight>(info);
        }
        
       
        PointLightSystem = _ECSManager->newSystem<PointLight>();
        {
            Info info;
            info.set(_ECSManager->getComponentType<PointLightComponent>());
            info.set(_ECSManager->getComponentType<TransformComponent>());
            _ECSManager->setSystemInfo<PointLight>(info);
        }
        
        SpotLightSystem = _ECSManager->newSystem<SpotLight>();
        {
            Info info;
            info.set(_ECSManager->getComponentType<SpotLightComponent>());
            info.set(_ECSManager->getComponentType<TransformComponent>());
            _ECSManager->setSystemInfo<SpotLight>(info);
        }
        
    };
    void update()
    {

        glUseProgram(_shaderProgram);
        
        unsigned int viewLoc = glGetUniformLocation(_shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera->getView()));

        unsigned int proyeccionLoc = glGetUniformLocation(_shaderProgram, "proyeccion");
        glUniformMatrix4fv(proyeccionLoc, 1, GL_FALSE, glm::value_ptr(_camera->getProjection()));
        
        unsigned int camPos = glGetUniformLocation(_shaderProgram, "viewPos");
        glUniform3f(camPos, _camera->position.x, _camera->position.y, _camera->position.z);
        
        
        updateLights();
        for (auto& gameObject : gameObjects)
        {
            auto& model = _ECSManager->getComponent<Model>(gameObject);
          
            auto& transform = _ECSManager->getComponent<TransformComponent>(gameObject);

            unsigned int modelLoc = glGetUniformLocation(_shaderProgram, "model");
            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_camera->model(transform.Translation, transform.Rotation, transform.Scale)));
            
            bool wireFrame = false;
            model.modelo.draw(_shaderProgram, wireFrame);
        }
        
    };
    
    
private:
    Camera* _camera;
    ECSManager* _ECSManager;
    uint32_t _shaderProgram;
    std::shared_ptr<DirectionalLight> DirectionalLightSystem;
    std::shared_ptr<PointLight> PointLightSystem;
    std::shared_ptr<SpotLight> SpotLightSystem;
    void updateLights()
    {
        DirectionalLightSystem->update(_shaderProgram, _ECSManager);
        PointLightSystem->update(_shaderProgram, _ECSManager);
        SpotLightSystem->update(_shaderProgram, _ECSManager);
    };
};



#endif /* Render_hpp */

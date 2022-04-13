//
//  DirectionalLight.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>

#include "System.hpp"
#include "DirectionalLightComponent.hpp"
#include "ECSManager.hpp"

extern ECSManager _ECSManager;

class DirectionalLight : public System
{
public:
    void update(uint32_t& shaderProgram, ECSManager* ECSManager)
    {
        
        
        int count = 0;
        for (auto& gameObject : gameObjects)
        {
            
            auto& light = ECSManager->getComponent<DirectionalLightComponent>(gameObject);
          
            std::string number = std::to_string(count);
            
            unsigned int lightDir = glGetUniformLocation(shaderProgram, ("directionalLights[" + std::to_string(0) + "].direction").c_str());
            glUniform3f(lightDir, light.lightDirection.x, light.lightDirection.y, light.lightDirection.z);
            
            unsigned int lightColor = glGetUniformLocation(shaderProgram, ("directionalLights[" + std::to_string(0) + "].diffuse").c_str());
            glUniform3f(lightColor, light.lightColor.x, light.lightColor.y, light.lightColor.z);
            
            unsigned int ambientIntensity = glGetUniformLocation(shaderProgram, ("directionalLights[" + std::to_string(0) + "].ambientIntensity").c_str());
            glUniform1f(ambientIntensity, light.ambientIntensity);
            
            unsigned int diffuseIntensity = glGetUniformLocation(shaderProgram, ("directionalLights[" + std::to_string(0) + "].diffuseIntensity").c_str());
            glUniform1f(diffuseIntensity, light.diffuseIntensity);

            count++;
        }
    }
};

#endif /* DirectionalLight_hpp */

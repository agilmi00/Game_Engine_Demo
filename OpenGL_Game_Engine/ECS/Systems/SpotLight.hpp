//
//  SpotLight.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include "System.hpp"
#include "SpotLightComponent.hpp"
#include "TransformComponent.hpp"
#include "ECSManager.hpp"

extern ECSManager _ECSManager;

class SpotLight : public System
{
public:
    void update(uint32_t& shaderProgram, ECSManager* ECSManager)
    {
        
        int cont = 0;
        for (auto& gameObject : gameObjects)
        {
            
            
            auto& transform = ECSManager->getComponent<TransformComponent>(gameObject);
            auto& light = ECSManager->getComponent<SpotLightComponent>(gameObject);
            
            std::string number = std::to_string(cont);
            
            unsigned int lightPos = glGetUniformLocation(shaderProgram, ("spotLights[" + number + "].position").c_str());
            glUniform3f(lightPos, transform.Translation.x, transform.Translation.y, transform.Translation.z);
            
            unsigned int lightRot = glGetUniformLocation(shaderProgram, ("spotLights[" + number + "].rotation").c_str());
            glUniform3f(lightRot, transform.Rotation.x, transform.Rotation.y, transform.Rotation.z);
            
            unsigned int lightColor = glGetUniformLocation(shaderProgram, ("spotLights[" + number + "].diffuse").c_str());
            glUniform3f(lightColor, light.lightColor.x, light.lightColor.y, light.lightColor.z);
            
            unsigned int diffuseIntensity = glGetUniformLocation(shaderProgram, ("spotLights[" + number + "].diffuseIntensity").c_str());
            glUniform1f(diffuseIntensity, light.diffuseIntensity);
            
            unsigned int maxRadius = glGetUniformLocation(shaderProgram, ("spotLights[" + number + "].maxRadius").c_str());
            glUniform1f(maxRadius, light.maxRadius);
            
            cont++;
        }
        unsigned int numberSpotL = glGetUniformLocation(shaderProgram, "numberSpotLights");
        glUniform1i(numberSpotL, cont);
    }
    
};
#endif /* SpotLight_hpp */

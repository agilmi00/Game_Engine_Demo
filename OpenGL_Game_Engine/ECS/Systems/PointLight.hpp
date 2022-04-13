//
//  PointLight.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>

#include "System.hpp"
#include "PointLightComponent.hpp"
#include "TransformComponent.hpp"
#include "ECSManager.hpp"

class PointLight : public System
{
public:
    
    void update(uint32_t& shaderProgram, ECSManager* ECSManager)
    {
        
        int cont = 0;
        for (auto& gameObject : gameObjects)
        {
            
            
            auto& transform = ECSManager->getComponent<TransformComponent>(gameObject);
            auto& light = ECSManager->getComponent<PointLightComponent>(gameObject);
            
            std::string number = std::to_string(cont);
            
            unsigned int lightPos = glGetUniformLocation(shaderProgram, ("pointLights[" + number + "].position").c_str());
            glUniform3f(lightPos, transform.Translation.x, transform.Translation.y, transform.Translation.z);

            
            unsigned int lightColor = glGetUniformLocation(shaderProgram, ("pointLights[" + number + "].diffuse").c_str());
            glUniform3f(lightColor, light.lightColor.x, light.lightColor.y, light.lightColor.z);
            
            unsigned int diffuseIntensity = glGetUniformLocation(shaderProgram, ("pointLights[" + number + "].diffuseIntensity").c_str());
            glUniform1f(diffuseIntensity, light.diffuseIntensity);
            
            unsigned int maxRadius = glGetUniformLocation(shaderProgram, ("pointLights[" + number + "].maxRadius").c_str());
            glUniform1f(maxRadius, light.maxRadius);
                  
            unsigned int lightColor2 = glGetUniformLocation(shaderProgram, "lightColor");
            glUniform3f(lightColor2, light.lightColor.x, light.lightColor.y, light.lightColor.z);


            unsigned int lightPos2 = glGetUniformLocation(shaderProgram, "lightPos");
            glUniform3f(lightPos2, transform.Translation.x, transform.Translation.y, transform.Translation.z);
            cont++;
        }
        unsigned int numberPointL = glGetUniformLocation(shaderProgram, "numberPointLights");
        glUniform1i(numberPointL, cont);
    }
    
};
#endif /* PointLight_hpp */

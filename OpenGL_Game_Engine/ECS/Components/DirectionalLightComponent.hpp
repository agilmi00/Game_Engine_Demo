//
//  DirectionalLightComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef DirectionalLightComponent_hpp
#define DirectionalLightComponent_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "glm/glm.hpp"
#include "BaseLight.hpp"

struct DirectionalLightComponent : public BaseLight
{
    glm::vec3 lightDirection = { -0.2f, -1.0f, -0.3f };
    float ambientIntensity = 0.2f;
   
};

#endif /* DirectionalLightComponent_hpp */

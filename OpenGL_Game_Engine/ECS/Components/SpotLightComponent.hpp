//
//  SpotLightComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef SpotLightComponent_hpp
#define SpotLightComponent_hpp

#include <stdio.h>
#include "glm/glm.hpp"

struct SpotLightComponent : public BaseLight
{
    float maxRadius = 5;
};

#endif /* SpotLightComponent_hpp */

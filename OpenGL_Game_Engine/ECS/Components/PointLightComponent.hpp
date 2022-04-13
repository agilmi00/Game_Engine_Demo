//
//  LightComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef PointLightComponent_hpp
#define PointLightComponent_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "glm/glm.hpp"
#include "BaseLight.hpp"


struct PointLightComponent : public BaseLight
{
    float maxRadius = 5;
};
#endif /* PointLightComponent_hpp */

//
//  TransformComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "glm/glm.hpp"
#include <stdio.h>

struct TransformComponent
{
    glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
};

#endif /* TransformComponent_hpp */

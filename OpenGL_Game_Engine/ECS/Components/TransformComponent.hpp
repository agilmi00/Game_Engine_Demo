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

#include "CustomMath.hpp"

struct TransformComponent
{
    mth::Vector3 Translation = { 0.0f, 0.0f, 0.0f };
    mth::Quatern Rotation = {mth::Vector3(0.0f, 0.0f, 0.0f), 1.0f };
    mth::Vector3 Scale = { 1.0f, 1.0f, 1.0f };
    mth::Vector3 RotEuler = { 0.0f, 0.0f, 0.0f };
};

#endif /* TransformComponent_hpp */

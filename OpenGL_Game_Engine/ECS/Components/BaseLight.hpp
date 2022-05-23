//
//  BaseLight.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef BaseLight_hpp
#define BaseLight_hpp

#include <stdio.h>


struct BaseLight
{
    mth::Vector3 lightColor = { 1.0f, 0.0f, 0.0f };
    float diffuseIntensity  = 0.2f;
};


#endif /* BaseLight_hpp */

//
//  ProjectileComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef ProjectileComponent_hpp
#define ProjectileComponent_hpp

#include <stdio.h>



struct ProjectileComponent
{
    glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
    glm::vec3 shootPosition;
};

#endif /* ProjectileComponent_hpp */

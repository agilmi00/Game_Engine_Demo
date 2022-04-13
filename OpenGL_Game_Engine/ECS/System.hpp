//
//  System.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef System_hpp
#define System_hpp

#include <stdio.h>
#include <set>
#include <bitset>
#include "GameObjectManager.hpp"



class System
{
public:
    std::set<GameObject> gameObjects;
};
#endif /* System_hpp */

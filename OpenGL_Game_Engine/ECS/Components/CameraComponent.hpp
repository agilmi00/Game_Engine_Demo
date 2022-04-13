//
//  CameraComponent.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include "Camera.hpp"

struct CameraComponent : Component<CameraComponent>
{
    Camera camera;
};

#endif /* CameraComponent_hpp */

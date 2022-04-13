//
//  Weapon.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda on 26/2/22.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <stdio.h>
#include "System.hpp"
#include "WeaponComponent.hpp"
#include "TransformComponent.hpp"
#include "Camera.hpp"
#include "ECSManager.hpp"


class Weapon : public System
{
public:
    void init(Camera* camera, std::unique_ptr<ECSManager> & ECSManager)
    {
        _camera = camera;
        _ECSManager = ECSManager.get();
    };
    void update(float deltaTime)
    {
        for (auto& gameObject : gameObjects)
        {
            auto& Weapon = _ECSManager->getComponent<WeaponComponent>(gameObject);
          
            _ECSManager->getComponent<TransformComponent>(gameObject).Translation = _camera->position;
        }
    };
private:
    Camera* _camera;
    ECSManager* _ECSManager;
};
#endif /* Weapon_hpp */

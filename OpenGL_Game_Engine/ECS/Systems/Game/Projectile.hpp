//
//  Projectile.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda on 28/2/22.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <stdio.h>
#include "System.hpp"
#include "ECSManager.hpp"

class Projectile : public System
{
public:
    void init(std::unique_ptr<ECSManager> & ECSManager)
    {
        _ECSManager = ECSManager.get();
    };
    void update(float deltaTime)
    {
        for (auto& gameObject : gameObjects)
        {
            trans = _ECSManager->getComponent<TransformComponent>(gameObject).Translation;
            auto Projectile = _ECSManager->getComponent<ProjectileComponent>(gameObject);
            if (mth::Distance(Projectile.shootPosition, trans) > 25) {
                
                gameObjectToRemove.push(gameObject);
//                _ECSManager->getComponent<TransformComponent>(gameObject).Translation
            }
            else{
                trans = trans + Projectile.direction * 1.2f;
            }
//            _ECSManager->getComponent<TransformComponent>(gameObject).Translation += Projectile.direction * 1.2f;
        }
        while(!gameObjectToRemove.empty())
        {
            _ECSManager->removeGameObject(gameObjectToRemove.front());
            gameObjectToRemove.pop();
        }
    };
private:
    Camera* _camera;
    ECSManager* _ECSManager;
    mth::Vector3 trans;
    std::queue<GameObject> gameObjectToRemove;
};

#endif /* Projectile_hpp */

//
//  ECSManager.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef ECSManager_hpp
#define ECSManager_hpp

#include <stdio.h>

#include "GameObjectManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"


class ECSManager
{
public:
    void init()
    {
        _componentManager = std::make_unique<ComponentManager>();
        _systemManager = std::make_unique<SystemManager>();
        _gameObjectManager = std::make_unique<GameObjectManager>();
    }

    template<typename System>
    std::shared_ptr<System> newSystem()
    {
        return _systemManager->newSystem<System>();
    }

    template<typename System>
    void setSystemInfo(Info info)
    {
        _systemManager->setInfo<System>(info);
    }

    GameObject createGameObject()
    {
        return _gameObjectManager->createGameObject();
    }
    
    void removeGameObject(GameObject gameObject)
    {
        
        _componentManager->removeGameObject(gameObject);
        _gameObjectManager->removeGameObject(gameObject);
        _systemManager->removeGameObject(gameObject);
        
    }

    template<typename Component>
    void newComponent()
    {
        _componentManager->newComponent<Component>();
    }

    template<typename Component>
    void addComponent(GameObject gameObject, Component component)
    {
        _componentManager->addComponent<Component>(gameObject, component);
        
        Info info = _gameObjectManager->getInfo(gameObject);
        info.set(_componentManager->getComponentType<Component>());
        
        _gameObjectManager->setInfo(gameObject, info);
        _systemManager->gameObjectUpdateInfo(gameObject, info);
    }
    Info getInfoGameObject(GameObject gameObject)
    {
        return _gameObjectManager->getInfo(gameObject);
    }

    template<typename Component>
    componentType getComponentType()
    {
        return _componentManager->getComponentType<Component>();
    }

    std::uint8_t getNumComponents()
    {
        return _componentManager->getSize();
    }
    template<typename Component>
    Component& getComponent(GameObject gameObject)
    {
        return _componentManager->getComponent<Component>(gameObject);
    }
private:
    std::unique_ptr<GameObjectManager> _gameObjectManager;
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<SystemManager> _systemManager;
    
};
#endif /* ECSManager_hpp */

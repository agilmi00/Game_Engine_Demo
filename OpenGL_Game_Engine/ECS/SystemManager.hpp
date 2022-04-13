//
//  SystemManager.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef SystemManager_hpp
#define SystemManager_hpp

#include <stdio.h>
#include <unordered_map>
#include "System.hpp"

using Info = std::bitset<MAX_COMPONENTS>;

class SystemManager
{
public:
    
    template<typename System>
    std::shared_ptr<System> newSystem()
    {
        const char* typeName = typeid(System).name();
        
        std::shared_ptr<System> system = std::make_shared<System>();
        _systems.insert({typeName, system}); // Initializer list
        
        return system;
        
    }
    
    template<typename System>
    void setInfo(Info info)
    {
        const char* typeName = typeid(System).name();
        _infos.insert({typeName, info});
    }
    
    void gameObjectUpdateInfo(GameObject gameObject, Info gameObjectInfo)
    {
        for (auto const& sys : _systems)
        {
            auto const& type = sys.first;
            auto const& system = sys.second;
            auto const& systemInfo = _infos[type];

            if ((systemInfo & ~gameObjectInfo).none()) // Compare 2 bitsets
            {
                system->gameObjects.insert(gameObject);
            }
            else
            {
                system->gameObjects.erase(gameObject);
            }
        }
    }
//    1010    1010
//    1101 -> 0010
//            0010
//                  Examples of bitwise operation performed to compare 2 infos.
//    1010    1010
//    1110 -> 0001
//            0000
    void removeGameObject(GameObject gameObject)
    {
        for (auto const& sys : _systems)
        {
            auto const& system = sys.second;
//            std::cout<<sys.first;
            system->gameObjects.erase(gameObject);
        }
    }
private:
    std::unordered_map<const char*, Info> _infos;
    std::unordered_map<const char*, std::shared_ptr<System>> _systems;
};

#endif /* SystemManager_hpp */

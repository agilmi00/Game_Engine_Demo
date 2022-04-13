//
//  GameObjectManager.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include <stdio.h>
#include <queue>
#include <array>


const uint32_t MAX_COMPONENTS = 10;
using Info = std::bitset<MAX_COMPONENTS>;
using GameObject = uint32_t;
const uint32_t MAX_OBJECTS = 1000;

class GameObjectManager
{
public:
    GameObjectManager()
    {
        for (GameObject gameObject = 0; gameObject < MAX_OBJECTS; gameObject++)
        {
            _availableGameObjects.push(gameObject); // Fill the queue with the ids that are available
        }
    }
    
    GameObject createGameObject()
    {
        // Create the GameObject with the available id that is at the beginning of the queue and then remove that id with pop.
        GameObject gameObject = _availableGameObjects.front();
        _availableGameObjects.pop();
        numberOfGameObjects++;
        
        return gameObject;
    }
    
    void removeGameObject(GameObject gameObject)
    {
        _availableGameObjects.push(gameObject); // Put the id in the queue to make it available again
        _infos[gameObject].reset();
        numberOfGameObjects--;
    }
    
    Info getInfo(GameObject gameObject)
    {
        return _infos[gameObject];
    }
    
    void setInfo(GameObject gameObject, Info info)
    {
        _infos[gameObject] = info;
    }
private:
    std::queue<GameObject> _availableGameObjects;
    std::array<Info, MAX_OBJECTS> _infos;
    uint32_t numberOfGameObjects;
};


#endif /* GameObjectManager_hpp */

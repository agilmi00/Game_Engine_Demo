//
//  Component.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

#include <any>
#include <map>
#include <memory>
#include <unordered_map>
#include "GameObjectManager.hpp"
template <typename ComponentType>
struct ComponentData
{
    uint32_t size = 0; // Number of objects in the array.
    std::array<ComponentType, MAX_OBJECTS> data;
};

class VirtualComponent
{
public:
    virtual ~VirtualComponent() = default;
    virtual void removeGameObject(GameObject gameObject){};
};

template <typename ComponentType>
class Component : public VirtualComponent
{
public:

    void insert(GameObject gameObject, ComponentType component)
    {
        componentData.data[componentData.size] = component;
        indexToGameObjectMap[componentData.size] = gameObject;
        gameObjectToIndexMap[gameObject] = componentData.size;
        
        componentData.size++;
    }
    void remove(GameObject gameObject)
    {
        if (gameObjectToIndexMap.find(gameObject) == gameObjectToIndexMap.end())
        {
            // Reordering of the data array to keep it free of fragmentation.
            // It copies the index of the last component and then saves that data in the place that was occupied by the component being deleted.
            uint32_t lastComponentIndex = componentData.size - 1;
            uint32_t removedComponentIndex = gameObjectToIndexMap[gameObject]; // Return de index associated to the gameObject
            componentData.data[removedComponentIndex] = componentData.data[lastComponentIndex];
            
            // Update maps
            GameObject lastElementGameObject = indexToGameObjectMap[lastComponentIndex];
            gameObjectToIndexMap[lastElementGameObject] = removedComponentIndex;
            indexToGameObjectMap[removedComponentIndex] = lastElementGameObject;
            
            // Delete pairs
            gameObjectToIndexMap.erase(gameObject);
            indexToGameObjectMap.erase(lastComponentIndex);
            
            componentData.size--;
        }
        
    }
    void removeGameObject(GameObject gameObject) override
    {
        if (gameObjectToIndexMap.find(gameObject) != gameObjectToIndexMap.end())
        {
            remove(gameObject);
        }
    }
    
    ComponentType& getData(GameObject gameObject)
    {
        return componentData.data[gameObjectToIndexMap[gameObject]];
    }
    
private:
    ComponentData<ComponentType> componentData; // Store all the data of a type of component
    std::unordered_map<GameObject, size_t> gameObjectToIndexMap;
    std::unordered_map<size_t, GameObject> indexToGameObjectMap;
};
#endif /* Component_hpp */

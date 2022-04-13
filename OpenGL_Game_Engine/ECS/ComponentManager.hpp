//
//  ComponentManager.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include <stdio.h>

#include <any>
#include <memory>
#include <unordered_map>
#include "GameObjectManager.hpp"
#include "Component.hpp"

using componentType = std::uint8_t;

class ComponentManager
{
public:
    
    template<typename ComponentT>
    void newComponent()
    {
        const char* typeName = typeid(ComponentT).name();

        _compTypes.insert({typeName, _nextType});
        _compArray.insert({typeName, std::make_shared<Component<ComponentT>>()});

        ++_nextType;
    }

    template<typename Component>
    componentType getComponentType()
    {
        const char* typeName = typeid(Component).name();

        return _compTypes[typeName]; // Return the Component ID
    }

    template<typename Component>
    void addComponent(GameObject gameObject, Component component)
    {
        getComponentArray<Component>()->insert(gameObject, component);
    }

    template<typename Component>
    void removeComponent(GameObject gameObject)
    {
        getComponentArray<Component>()->remove(gameObject);
    }
    
    void removeGameObject(GameObject gameObject)
    {
        for (auto const& pair : _compArray)
        {
            auto const& component = pair.second;

            component->removeGameObject(gameObject);
        }
    }
    
    std::uint8_t getSize()
    {
        return _compTypes.size();
    }
    
    template<typename Component>
    Component& getComponent(GameObject gameObject)
    {
        return getComponentArray<Component>()->getData(gameObject);
    }
    
private:
    
    componentType _nextType{};
    std::unordered_map<const char*, std::shared_ptr<VirtualComponent>> _compArray;
    std::unordered_map<const char*, componentType> _compTypes; //Map [ComponentName:ID]
    

    template<typename component>
    std::shared_ptr<Component<component>> getComponentArray()
    {
        const char* typeName = typeid(component).name();
        
        return std::static_pointer_cast<Component<component>>(_compArray[typeName]);
    }
};
#endif /* ComponentManager_hpp */

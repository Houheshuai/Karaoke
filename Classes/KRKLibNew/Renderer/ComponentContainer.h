#ifndef __FRAMEWORK_COMCONTAINER_H__
#define __FRAMEWORK_COMCONTAINER_H__

#include "Base/Map.h"
#include <string>

class Component;
class Node;

class ComponentContainer
{
protected:
    /**
     * @js ctor
     */
    ComponentContainer(Node* node);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    ~ComponentContainer();
    
	/**
     * @js getComponent
     */
	Component* get(const std::string& name) const;

    bool add(Component *com);
    bool remove(const std::string& name);
    bool remove(Component *com);
    void removeAll();
    void visit(float delta);
    
    void onEnter();
    void onExit();
    
    bool isEmpty() const { return _componentMap.empty(); } 
private:
    std::unordered_map<std::string, Component*> _componentMap;
    Node *_owner;
    
    friend class Node;
};

#endif  // __FRAMEWORK_COMCONTAINER_H__

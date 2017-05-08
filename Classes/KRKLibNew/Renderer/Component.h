#ifndef __FRAMEWORK_COMPONENT_H__
#define __FRAMEWORK_COMPONENT_H__

#include <string>
#include "Base/Ref.h"

class Node;

enum {
    kComponentOnEnter,
    kComponentOnExit,
    kComponentOnAdd,
    kComponentOnRemove,
    kComponentOnUpdate
};

class Component : public Ref
{
public:
    static Component* create();

    /**
     * @js NA
     * @lua NA
     */
    virtual ~Component();

    virtual bool init();

    bool isEnabled() const { return _enabled; }
    virtual void setEnabled(bool enabled);
    
    const std::string& getName() const { return _name; }
    virtual void setName(const std::string& name) { _name = name; }
    
    Node* getOwner() const { return _owner; }
    virtual void setOwner(Node *owner);

    virtual void update(float delta);
    virtual bool serialize(void* r);

    virtual void onEnter();
    virtual void onExit();
    virtual void onAdd();
    virtual void onRemove();

    Component();

protected:
    Node* _owner;
    std::string _name;
    bool _enabled;
    
};

#endif  // __FRAMEWORK_COMPONENT_H__

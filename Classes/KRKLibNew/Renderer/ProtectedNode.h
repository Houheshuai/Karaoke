#ifndef __PROTECTEDCNODE_H__
#define __PROTECTEDCNODE_H__

#include "Renderer/Node.h"

/**
 *@brief A inner node type mainly used for UI module.
 * It is useful for composing complex node type and it's children are protected.
 */
class  ProtectedNode : public Node
{
public:
    /**
     * Creates a ProtectedNode with no argument.
     *@return A instance of ProtectedNode.
     */
    static ProtectedNode * create(void);
    
    /// @{
    /// @name Children and Parent
    
    /**
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child A child node
     */
    virtual void addProtectedChild(Node * child);
    /**
     * Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     */
    virtual void addProtectedChild(Node * child, int localZOrder);
    /**
     * Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @param tag       An integer to identify the node easily. Please refer to `setTag(int)`
     */
    virtual void addProtectedChild(Node* child, int localZOrder, int tag);
    /**
     * Gets a child from the container with its tag.
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node object whose tag equals to the input parameter.
     */
    virtual Node * getProtectedChildByTag(int tag);
    
    ////// REMOVES //////
    
    /**
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param child     The child node which will be removed.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeProtectedChild(Node* child, bool cleanup = true);
    
    /**
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param tag       An integer number that identifies a child node.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeProtectedChildByTag(int tag, bool cleanup = true);
    
    /**
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`.
     */
    virtual void removeAllProtectedChildren();
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false otherwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllProtectedChildrenWithCleanup(bool cleanup);
    
    /**
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param localZOrder Z order for drawing priority. Please refer to setLocalZOrder(int)
     */
    virtual void reorderProtectedChild(Node * child, int localZOrder);
    
    /**
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame
     */
    virtual void sortAllProtectedChildren();
    
    /// @} end of Children and Parent
    
    /**
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, unsigned int parentFlags) override;
    
    virtual void cleanup() override;
    
    virtual void onEnter() override;
    
    /** Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish() override;
    
    /**
     * Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    
    /**
     * Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart() override;

    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void disableCascadeColor() override;
    virtual void disableCascadeOpacity()override;
    //virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    ProtectedNode();
    virtual ~ProtectedNode();
    
protected:
    
    /// helper that reorder a child
    void insertProtectedChild(Node* child, int z);
    
    Vector<Node*> _protectedChildren;        ///< array of children nodes
    bool _reorderProtectedChildDirty;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ProtectedNode);
};


#endif // __CPROTECTEDCNODE_H__

#ifndef __CLIPPING_RECTANGLE_NODE_H__
#define __CLIPPING_RECTANGLE_NODE_H__

#include "Renderer/Node.h"
#include "Renderer/CustomCommand.h"


class ClippingRectangleNode : public Node
{    
public:
    /**
    @brief Create node with specified clipping region.
    @param clippingRegion Specify the clipping rectangle.
    @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
    */
    static ClippingRectangleNode* create(const Rect& clippingRegion);
    /**
    @brief Create a clipping rectangle node.
    @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
    */
    static ClippingRectangleNode* create();
    
    /**
    @brief Get the clipping rectangle.
    @return The clipping rectangle.
    */
    const Rect& getClippingRegion() const {
        return _clippingRegion;
    }
    /**
    @brief Set the clipping rectangle.
    @param clippingRegion Specify the clipping rectangle.
    */
    void setClippingRegion(const Rect& clippingRegion);
    
    /**
    @brief Get whether the clipping is enabled or not.
    @return Whether the clipping is enabled or not. Default is true.
    */
    const bool isClippingEnabled() const {
        return _clippingEnabled;
    }

    /**
    @brief Enable/Disable the clipping.
    @param enabled Pass true to enable clipping. Pass false to disable clipping.
    */
    void setClippingEnabled(bool enabled) {
        _clippingEnabled = enabled;
    }

    //virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, unsigned int parentFlags);

protected:
    ClippingRectangleNode()
    : _clippingEnabled(true)
    {
    }
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    
    Rect _clippingRegion;
    bool _clippingEnabled;
    
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
};

#endif


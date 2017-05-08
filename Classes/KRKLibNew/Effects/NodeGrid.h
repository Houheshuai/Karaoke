#ifndef __MISCNODE_GRID_NODE_H__
#define __MISCNODE_GRID_NODE_H__

#include "Renderer/Node.h"
#include "Renderer/GroupCommand.h"
#include "Renderer/CustomCommand.h"

class GridBase;

class NodeGrid : public Node
{
public:
    /** Create a Grid Node.
     *
     * @return An autorelease Grid Node.
     */
    static NodeGrid* create();
    
    static NodeGrid* create(const Rect& rect);
    
    /** Get a Grid Node. 
     *
     * @return Return a GridBase.
     */
    GridBase* getGrid() { return _nodeGrid; }
    /**
     * @js NA
     */
    const GridBase* getGrid() const { return _nodeGrid; }

    /**
     * Changes a grid object that is used when applying effects.
     *
     * @param grid  A Grid object that is used when applying effects.
     */
    void setGrid(GridBase *grid);
    
    /** Set the Grid Target. 
     *
     * @param target A Node is used to set the Grid Target.
     */
    void setTarget(Node *target);
    
    /**
     * @brief Set the effect grid rect.
     * @param gridRect The effect grid rect.
     */
    inline void setGridRect(const Rect& gridRect){_gridRect = gridRect;}
    /**
     * @brief Get the effect grid rect.
     * @return Return the effect grid rect.
     */
    inline const Rect& getGridRect() const { return _gridRect;}

    // overrides
	virtual void visit();
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, unsigned int parentFlags);

public:
    NodeGrid();
    virtual ~NodeGrid();

protected:
    void onGridBeginDraw();
    void onGridEndDraw();

    Node* _gridTarget;
    GridBase* _nodeGrid;
    GroupCommand _groupCommand;
    CustomCommand _gridBeginCommand;
    CustomCommand _gridEndCommand;
    
    Rect _gridRect;

	Renderer	*_renderer;

private:
    DISALLOW_COPY_AND_ASSIGN(NodeGrid);
};

#endif

#ifndef __ACTION_PAGETURN3D_ACTION_H__
#define __ACTION_PAGETURN3D_ACTION_H__

#include "Action/ActionGrid3D.h"


/**
 @brief This action simulates a page turn from the bottom right hand corner of the screen.
 
 @details It's not much use by itself but is used by the PageTurnTransition.
         Based on an original paper by L Hong et al.
         http://www.parc.com/publication/1638/turning-pages-of-3d-electronic-books.html
  
 @since v0.8.2
 */
class PageTurn3D : public Grid3DAction
{
public:
    /**
     * @js NA 
     */
    virtual GridBase* getGrid() override;

    /**
    @brief Create an action with duration, grid size.
    @param duration Specify the duration of the PageTurn3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @return If the creation success, return a pointer of PageTurn3D action; otherwise, return nil.
    */
    static PageTurn3D* create(float duration, const Size& gridSize);

    // Overrides
	virtual PageTurn3D* clone() const override;
    virtual void update(float time) override;
};

class PageCube : public Grid3DAction
{
public:
    /**
     * @js NA 
     */
    virtual GridBase* getGrid() override;

    /**
    @brief Create an action with duration, grid size.
    @param duration Specify the duration of the PageTurn3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @return If the creation success, return a pointer of PageTurn3D action; otherwise, return nil.
    */
    static PageCube* create(float duration, const Size& gridSize);

    // Overrides
	virtual PageCube* clone() const override;
    virtual void update(float time) override;
};

#endif // __ACTION_PAGETURN3D_ACTION_H__

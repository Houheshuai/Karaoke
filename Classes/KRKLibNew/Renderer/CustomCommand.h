#ifndef __CUSTOMCOMMAND_H_
#define __CUSTOMCOMMAND_H_

#include "Renderer/RenderCommand.h"

/**
Custom command is used for call custom openGL command which can not be done by other commands,
such as stencil function, depth functions etc. The render command is executed by calling a call back function.
*/
class CustomCommand : public RenderCommand
{
public:
	/**Constructor.*/
    CustomCommand();
    /**Destructor.*/
    ~CustomCommand();
    
public:
	/**
	Init function.
	@param globalZOrder GlobalZOrder of the render command.
	@param modelViewTransform When in 3D mode, depth sorting needs modelViewTransform.
	@param flags Use to identify that the render command is 3D mode or not.
	*/
    void init(float globalZOrder, const Mat4& modelViewTransform, unsigned int flags);
    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);

    /**
    Execute the render command and call callback functions.
    */
    void execute();
    //TODO: This function is not used, it should be removed.
    inline bool isTranslucent() { return true; }
    /**Callback function.*/
    std::function<void()> func;

protected:
};

#endif //__CUSTOMCOMMAND_H_

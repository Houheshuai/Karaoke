#ifndef __EFFECTS_GRABBER_H__
#define __EFFECTS_GRABBER_H__

#include "Base/Ref.h"
#include "Renderer/OpenGLESHeaders.h"

class Texture2D;

/** FBO class that grabs the the contents of the screen */
class Grabber : public Ref
{
public:
    /**
    Constructor.
     * @js ctor
     */
    Grabber(void);
    /**
    Destructor.
     * @js NA
     * @lua NA
     */
    ~Grabber(void);
    /**Init the grab structure, will set the texture as the FBO color attachment.*/
    void grab(Texture2D *texture);
    /**Begin capture the screen, which will save the old FBO, clear color, and set the new FBO, clear the background.*/
    void beforeRender(Texture2D *texture);
    /**After capture, will reset the old FBO and clear color.*/
    void afterRender(Texture2D *texture);

protected:
    GLuint _FBO;
    GLint _oldFBO;
    GLfloat _oldClearColor[4];
};

#endif // __EFFECTS_GRABBER_H__

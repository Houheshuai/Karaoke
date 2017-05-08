#ifndef _StencilStateManager_H
#define _StencilStateManager_H

#include "Base/Macros.h"
#include "Renderer/OpenGLESHeaders.h"

class StencilStateManager
{
public:
    StencilStateManager();
    void onBeforeVisit();
    void onAfterDrawStencil();
    void onAfterVisit();
    void setAlphaThreshold(GLfloat alphaThreshold);
    void setInverted(bool inverted);
    bool isInverted()const;
    GLfloat getAlphaThreshold()const;
private:
    DISALLOW_COPY_AND_ASSIGN(StencilStateManager);
    static GLint s_layer;
    /**draw fullscreen quad to clear stencil bits
     */
    void drawFullScreenQuadClearStencil();
    
    
    GLfloat _alphaThreshold;
    bool    _inverted;
    
    GLboolean _currentStencilEnabled;
    GLuint _currentStencilWriteMask;
    GLenum _currentStencilFunc;
    GLint _currentStencilRef;
    GLuint _currentStencilValueMask;
    GLenum _currentStencilFail;
    GLenum _currentStencilPassDepthFail;
    GLenum _currentStencilPassDepthPass;
    GLboolean _currentDepthWriteMask;
    
    GLboolean _currentAlphaTestEnabled;
    GLenum _currentAlphaTestFunc;
    GLclampf _currentAlphaTestRef;
    
    GLint _mask_layer_le;
};

#endif // _StencilStateManager_H

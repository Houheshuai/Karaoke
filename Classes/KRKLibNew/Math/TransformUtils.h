#ifndef __SUPPORT_TRANSFORM_UTILS_H__
#define __SUPPORT_TRANSFORM_UTILS_H__

// TODO: when in MAC or windows, it includes <OpenGL/gl.h>
#include "Renderer/OpenGLESHeaders.h"
#include "Base/Macros.h"


struct AffineTransform;
/**@{
 Conversion between mat4*4 and AffineTransform.
 @param m The Mat4*4 pointer.
 @param t Affine transform.
 */
void CGAffineToGL(const AffineTransform &t, GLfloat *m);
void GLToCGAffine(const GLfloat *m, AffineTransform *t);



#endif // __SUPPORT_TRANSFORM_UTILS_H__

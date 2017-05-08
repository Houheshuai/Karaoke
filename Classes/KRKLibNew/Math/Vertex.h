#ifndef __MKVERTEX_H__
#define __MKVERTEX_H__

#include "Math/Math.h"
// converts a line to a polygon 
void VertexLineToPolygon(Vec2 *points, float stroke, Vec2 *vertices, unsigned int offset, unsigned int nuPoints);

// returns whether or not the line intersects
bool VertexLineIntersect(float Ax, float Ay,
                             float Bx, float By,
                             float Cx, float Cy,
                             float Dx, float Dy, float *T);


#endif


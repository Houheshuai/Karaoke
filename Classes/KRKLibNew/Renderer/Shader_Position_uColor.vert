const char* Position_uColor_vert = STRINGIFY(
attribute vec4 a_Position;
uniform vec4 u_Color;
uniform float u_PointSize;
varying lowp vec4 v_fragmentColor;

void main()
{
    gl_Position = MK_PMatrix * a_Position;
    gl_PointSize = u_PointSize;
    v_fragmentColor = u_Color;
}
);

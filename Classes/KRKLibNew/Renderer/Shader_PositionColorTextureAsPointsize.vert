const char* PositionColorTextureAsPointsize_vert = STRINGIFY(
attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_TexCoord;
varying lowp vec4 v_fragmentColor;

void main()
{
    gl_Position = MK_PMatrix * a_Position;
    gl_PointSize = a_TexCoord.x;
    v_fragmentColor = a_Color;
}
);

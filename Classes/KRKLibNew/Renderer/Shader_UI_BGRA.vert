const char* DrawUI_BGRA_vert = STRINGIFY(
attribute vec4 a_Position;
attribute vec2 a_TexCoord;
attribute vec4 a_Color;
varying vec2 v_texCoord;
\n#ifdef ANDROID\n
varying lowp vec4 v_fragmentColor;\n
\n#else\n
varying vec4 v_fragmentColor;\n
\n#endif\n
void main()
{
    gl_Position = MK_PMatrix * a_Position;
    v_texCoord = a_TexCoord;
	v_fragmentColor = a_Color;\n
}
);
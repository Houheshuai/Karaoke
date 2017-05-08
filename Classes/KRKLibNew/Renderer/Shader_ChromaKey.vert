const char* Chroma_vert = STRINGIFY(
attribute vec4 a_Position;\n
attribute vec2 a_TexCoord;\n
attribute vec4 a_Color;
varying vec2 v_TexCoord;\n
varying lowp vec4 v_fragmentColor;\n
void main()\n
{\n
 gl_Position = MK_PMatrix * a_Position;\n
 v_TexCoord = a_TexCoord;\n
 v_fragmentColor = a_Color;\n
}
);

const char* YUVTexture_vert = STRINGIFY(
attribute vec4 a_Position;
attribute vec2 a_TexCoord;
varying mediump vec2 v_texCoord;

void main()
{
    gl_Position = MK_PMatrix * a_Position;
    v_texCoord = a_TexCoord;
}
);
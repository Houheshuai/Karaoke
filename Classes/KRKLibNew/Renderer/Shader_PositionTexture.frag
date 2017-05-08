const char* PositionTexture_frag = STRINGIFY(
varying vec2 v_texCoord;
void main()
{
    gl_FragColor =  texture2D(MK_Texture0, v_texCoord);
}
);

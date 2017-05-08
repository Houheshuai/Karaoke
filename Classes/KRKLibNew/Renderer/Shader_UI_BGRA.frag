const char* DrawUI_BGRA_frag = STRINGIFY(
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;\n
void main()
{
    gl_FragColor = v_fragmentColor * texture2D(MK_Texture0, v_texCoord).bgra;
}
);

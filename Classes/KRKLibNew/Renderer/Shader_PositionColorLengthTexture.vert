const char* PositionColorLengthTexture_vert = STRINGIFY(
attribute mediump vec4 a_Position;
attribute mediump vec2 a_TexCoord;
attribute mediump vec4 a_Color;
varying mediump vec4 v_Color;
varying mediump vec2 v_Texcoord;
void main()
{
    v_Color = vec4(a_Color.rgb * a_Color.a, a_Color.a);
    v_Texcoord = a_TexCoord;

    gl_Position = MK_PMatrix * a_Position;
}
);

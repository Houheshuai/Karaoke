const char* PositionColorLengthTexture_frag = STRINGIFY(
varying mediump vec4 v_Color;\n
varying mediump vec2 v_Texcoord;\n
void main()
{
   gl_FragColor = v_Color*step(0.0, 1.0 - length(v_Texcoord));
}
);

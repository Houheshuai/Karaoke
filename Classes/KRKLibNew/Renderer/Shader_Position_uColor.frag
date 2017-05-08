const char* Position_uColor_frag = STRINGIFY(
precision lowp float;
varying vec4 v_fragmentColor;

void main()
{
    gl_FragColor = v_fragmentColor;
}
);

const char* YUVTexture_frag = STRINGIFY(
varying vec2 v_texCoord;
void main()
{
	mediump vec3 yuv;
    lowp vec3 rgb;
    yuv.x = texture2D(MK_Texture0, v_texCoord).r;
    yuv.y = texture2D(MK_Texture1, v_texCoord).r - 0.5;
    yuv.z = texture2D(MK_Texture2, v_texCoord).r - 0.5;
	rgb = mat3(1, 1, 1,
          0, -.21482, 2.12798,
         1.28033, -.38059, 0) * yuv;
	gl_FragColor = vec4(rgb, 1);
}
);

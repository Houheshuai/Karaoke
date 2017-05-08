const char* LyricGrayOneColor_frag = STRINGIFY(
\n#ifdef ANDROID\n
uniform lowp vec4 Color1;\n
//uniform lowp vec4 Color2;\n
//uniform mediump float Percent;\n
\n#else\n
uniform vec4 Color1;\n
//uniform vec4 Color2;\n
//uniform float Percent;\n
\n#endif\n
varying vec2 v_TexCoord;\n
varying vec4 v_fragmentColor;\n
void main()\n
{\n
	vec4 sample = texture2D(MK_Texture0, v_TexCoord);
	float x = v_TexCoord.x;\n
	//float sep = Percent;\n
	vec4 textColor;
	//if(x >= sep)
	//{
		textColor = Color1;
	//}
	//else
	//{
	//	textColor = Color2;
	//}
	//float dist = sample.a;
	//float width = 0.06;
	//float alpha = smoothstep(0.5-width, 0.5+width, dist);
	//glow
	//float mu = smoothstep(0.5, 1.0, sqrt(dist));
	//vec4 color = textColor * alpha;
	//gl_FragColor = vec4(color.rgb, max(alpha,mu)*color.a * v_fragmentColor.a);

	gl_FragColor = vec4(textColor.r, textColor.g, textColor.b, textColor.a * sample.a * v_fragmentColor.a);
}
);

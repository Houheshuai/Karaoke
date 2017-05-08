const char* LyricGray_frag = STRINGIFY(
\n#ifdef ANDROID\n
precision lowp float;\n
uniform lowp vec4 Color1;\n
uniform lowp vec4 Color2;\n
uniform lowp vec4 Color3;\n
uniform lowp vec4 Color4;\n
uniform lowp float Percent;\n
\n#else\n
precision lowp float;\n
uniform vec4 Color1;\n
uniform vec4 Color2;\n
uniform vec4 Color3;\n
uniform vec4 Color4;\n
uniform float Percent;\n
\n#endif\n

varying vec2 v_TexCoord;
varying vec4 v_fragmentColor;
//float intensity_offset = 2.0;\n
//float intensity_scale = 1.0;\n 
vec4 composite(vec4 over, vec4 under)\n 
{\n   
	return over + (1.0 - over.a)*under;\n 
}\n 
void main()\n
{\n
	vec4 sample = texture2D(MK_Texture0, v_TexCoord);
    //float fontAlpha = sample.a; 
    //float outlineAlpha = sample.r;
	vec4 textColor;\n
	vec4 outlineColor;\n
	float x = v_TexCoord.x;\n
	float sep = Percent;\n
	if(x > sep)\n
	{\n
		textColor = Color1;
		outlineColor = Color3;
		//outlinecolor.a = outlineAlpha;
		//u_textColor.a = fontAlpha;
		//float gray = dot(outlinecolor.rgb, vec3(0.3, 0.59, 0.11));  
		//float new_intensity = (gray + intensity_offset) * intensity_scale;  
		// fixed color  
		//outlinecolor = outlinecolor * new_intensity; 
		//outlineAlpha = outlinecolor.a;
	}\n
	else\n
	{\n
		textColor = Color2;
		outlineColor = Color4;
		//outlinecolor.a = outlineAlpha;
		//u_textColor.a = fontAlpha;
	}\n
	
	if ((sample.a + sample.r) > 0.0){
		//if(sample.r > 0.0)
		//{
			vec4 color = textColor * sample.a + outlineColor * (1.0 - sample.a);
			sample.a = clamp(sample.a * 2.0, 0.0, 1.0);
			vec4 texColor = vec4(color.rgb,max(sample.a, sample.r)*color.a);
			//vec4 texColor = vec4(color.rgb, sample.a * textColor.a + sample.r * outlineColor.a * textColor.a);
			gl_FragColor = vec4(texColor.r, texColor.g, texColor.b, texColor.a * v_fragmentColor.a);
		//}
		//else
		//{
		//	vec2 shadowOffset = vec2(-0.05, -0.05);
		//	vec4 sampleShadow = texture2D(MK_Texture0, v_TexCoord + shadowOffset);
		//	float shadowMask = sample.a;
		//	vec4 shadowColor = vec4(0.1, 0.1, 0.1, 1.0);
		//	vec4 color = textColor * sample.a + outlineColor * (1.0 - sample.a);
		//	sample.a = clamp(sample.a * 2.0, 0.0, 1.0);
		//	vec4 texColor = vec4(color.rgb,max(sample.a, sample.r)*color.a);
		//	vec4 color = textColor * sample.a + shadowColor * (1.0 - sample.a);
		//	gl_FragColor = vec4(texColor.r, texColor.g, texColor.b, texColor.a * v_fragmentColor.a);
			//gl_FragColor = composite(texColor, shadowColor); 
			//gl_FragColor.a *= v_fragmentColor.a;
			//outlineColor = vec4(0.2, 0.2, 0.2, 0.5);
			//float dist = sample.a;
			//float width = 1.0;
			//float alpha = smoothstep(0.5-width, 0.5+width, dist) * textColor.a;
			//gl_FragColor = vec4(textColor.rgb, alpha * v_fragmentColor.a);
			//float dist = sample.a;
			//float width = 0.04;
			//float alpha = smoothstep(0.5-width, 0.5+width, dist);
			//glow
			//float mu = smoothstep(0.5, 1.0, sqrt(dist));
			//vec4 color = outlineColor*(1.0-alpha) + textColor*alpha;
			//gl_FragColor = vec4(color.rgb, max(alpha,mu)*color.a * v_fragmentColor.a);
		//}
    }
    else {
        discard;
    }

	//vec3 color = (textColor.rgb * sample.a) + (outlineColor.rgb * sample.r);
	// make the main alpha more pronounced, makes small text sharper
	//sample.a = clamp(sample.a * 2.0, 0.0, 1.0);

	// alpha is the sum of main alpha and outline alpha
	// main alpha is main font color alpha
	// outline alpha is the stroke or shadow alpha

	//float mainAlpha = sample.a * textColor.a;
	//float outlineAlpha = sample.r * outlineColor.a * textColor.a;
	//gl_FragColor = vec4(color, (mainAlpha + outlineAlpha) * v_fragmentColor.a);
}
);

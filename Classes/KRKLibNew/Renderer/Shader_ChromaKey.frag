const char* Chroma_frag = STRINGIFY(
varying mediump vec2 v_TexCoord;
varying vec4 v_fragmentColor;
//vec3		lowColor = vec3(0.321, 0.422, 0.117);
//vec3		highColor = vec3(0.545, 0.554, 0.388);
vec3		lowColor = vec3(0.0, 0.0, 0.0);
vec3		highColor = vec3(1.0, 0.392, 1.0);
bool		useCrominance = true;
//bool		maskOutput = false;
float		threshold = 0.8;
float		slope = 0.6;
float		alphaLowPass = 0.8;
float		alphaHighPass = 0.01;

//vec3 Rgb2YCbCr(vec3 color)
//{
//	return vec3((0.299 * color.r) + (0.587 * color.g) + (0.114 * color.b),
//				0.5 - (0.168736 * color.r) + (0.331264 * color.g) + (0.5 * color.b),
//				0.5 + (0.5 * color.r) + (0.418688 * color.g) + (0.081312 * color.b) );
//}
			
vec3 RGB2YCbCr(vec3 c)
{
	return vec3(
		0.2989 * c.r + 0.5866 * c.g + 0.114 * c.b,
		-0.1687 * c.r - 0.3313 * c.g + 0.5000 * c.b + 0.50196,
		0.5000 * c.r - 0.418688 * c.g - 0.081312 * c.b + 0.50196);
}
			
vec3 YCbCr2RGB(vec3 c)
{
	vec3 rgb = mat3(1, 1, 1,
          0, -.21482, 2.12798,
         1.28033, -.38059, 0) * c;
	return rgb;

	//return vec3(
	//			c[0] + 0.0000 * c[1] + 1.4022 * c[2],
	//			c[0] - 0.3456 * c[1] - 0.7145 * c[2],
	//			c[0] + 1.7710 * c[1] + 0.0000 * c[2] );
}
			
float ChromaKeyAlpha(vec3 fg, vec3 matte)
{
	float d = abs(length(abs(matte - fg))); 
	float edge = threshold * (1.0 - slope); 
	return smoothstep(edge, threshold, d);
}

vec4 ChromaKey(vec3 fg, vec3 matte)
{
	float d = abs(length(abs(matte - fg))); 
	float edge = threshold * (1.0 - slope); 
	float alpha = smoothstep(edge, threshold, d);
	return vec4(fg, alpha);
}

void main()
{
	vec4 ori = vec4(texture2D(MK_Texture0, v_TexCoord).rgb, 1.0);
	vec4 _texCol1 = texture2D( MK_Texture0,  vec2(v_TexCoord.x, v_TexCoord.y+0.001));
	vec4 _texCol2 = texture2D( MK_Texture0,  vec2(v_TexCoord.x-0.001, v_TexCoord.y));
	vec4 _texCol3 = texture2D( MK_Texture0,  vec2(v_TexCoord.x+0.001, v_TexCoord.y));

	vec3 fg = RGB2YCbCr(ori.rgb);

	vec3 fg1 = RGB2YCbCr(_texCol1.rgb);
	vec3 fg2 = RGB2YCbCr(_texCol2.rgb);
	vec3 fg3 = RGB2YCbCr(_texCol3.rgb);

	vec3 low = lowColor; // 
	vec3 high = highColor; // 
	float alpha = 1.0;

	if(useCrominance)
	{
		if( 
			fg.r > low.r && fg.r < high.r &&
			fg.g > low.g && fg.g < high.g &&
			fg.b > low.b && fg.b < high.b ) 
		{
			alpha = 0.0;
		}
		else
		{
			int needstroke = 0;
			if(
				fg1.r > low.r && fg1.r < high.r &&
				fg1.g > low.g && fg1.g < high.g &&
				fg1.b > low.b && fg1.b < high.b
			)
			{
				needstroke++;
			}
			if( 
				fg2.r > low.r && fg2.r < high.r &&
				fg2.g > low.g && fg2.g < high.g &&
				fg2.b > low.b && fg2.b < high.b
			)
			{
				needstroke++;
			}
			if( 
				fg3.r > low.r && fg3.r < high.r &&
				fg3.g > low.g && fg3.g < high.g &&
				fg3.b > low.b && fg3.b < high.b
			)
			{
				needstroke++;
			}

			if (needstroke == 1)
			{
			   ori.r = 0.8;
			   ori.g = 0.8;
			   ori.b = 0.8;
			   alpha = 0.3;
			}
			else
			{
				alpha = 1.0;//ChromaKeyAlpha(fg, low);
			}
		}
	}

	//if(alpha > alphaLowPass)
	//	alpha = 1.0;

	//if(alpha < alphaHighPass)
	//	alpha = 0.0;

	//gl_FragColor =  vec4(alpha, alpha, alpha, alpha); //Mask
	gl_FragColor = vec4(ori.bgr, alpha) * v_fragmentColor;
}
);


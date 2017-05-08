#ifndef _COMMON_DEFINE_H
#define _COMMON_DEFINE_H
#include <string>

//MUS歌曲返回的属性
enum KRK_Font_Language
{
	L_CHN = 0x0000,
	L_ENG,
	L_KOR,
	L_THA,
	L_VIE,
	L_JAP,
	L_WST,
	L_RUS,
	L_DAN,
	L_OTH,
	L_XLE,
	L_JIS,
	L_FANWEN,
	L_POL,		// Polish
	L_BUR,		// Burmese
	L_DAI,		// dai wen
	L_MON,		// Mongolian 
	L_TUR,		// Turkish 
	L_ARAB,		// arab


	L_BENGALI = 0xF0,
	L_GURMUKHI,
	L_GUJARATI,
	L_ORIYA,
	L_TAMIL,
	L_TELUGU,
	L_KANNADA,
	L_MALAYALAM,
	L_SINHALA,

	L_KHMER,	//campodia
	L_KOR_DVD,
	L_HEBREW,
	
	MAX_LANTYPE
	
};

//MUK歌曲定义的属性
enum KRK_Song_Language
{
	SONG_CHN = 1,
	SONG_ENG = 4,
	SONG_JAP = 5,
	SONG_KOR = 6,
	SONG_VN = 7,
	SONG_THA = 8,
	SONG_RU = 9,
	SONG_BRA = 10,
	SONG_SPA = 11,
	SONG_PHI = 12,
	SONG_ITA = 13,
	SONG_GER = 14,
	SONG_FRA = 15,
	SONG_POR = 16,
	SONG_LATIN = 17,
	SONG_INI = 18,//
	SONG_JIS = 19,//JIS日文
	SONG_XLE = 20,//西里尔文
	SONG_HOL = 21,//荷兰文
	SONG_INDU = 22,//"INDIAN"
	SONG_INDI = 23,//"INDOIRANIA",*/
	SONG_PERS = 24,//"PERSIAN",*/
	SONG_HEB = 25,//"HEBREW",*/
	SONG_POL = 26,//"POLAND",*/
	SONG_BEN = 27,//"BENGALI",*/
	
	SONG_Bhajans = 28,

	SONG_Malaysia = 29,
	SONG_BGD = 30,
	SONG_MALA = 31,/*Malayalam*/
	SONG_MMR = 32,
	SONG_DaiWen = 33,
	SONG_KHM = 34,
	SONG_MON = 35,
	SONG_ARAB = 36,
	SONG_TUR = 37,  //土耳其
	SONG_JINPO = 38,//

	// indian local language
	SONG_Garba = 39,
	SONG_Gujarati = 40,
	SONG_Malayalum = 41,
	SONG_Marathi = 42,
	SONG_Tamil = 43,
	SONG_Telugu = 44,
	SONG_Bengali = 45,
	SONG_Kannada = 46,
	SONG_Sinhala = 47,
	SONG_Konkani = 48,
	SONG_Urdu = 49,
	SONG_Punjabi = 50,

	SONG_Translate = 51,
	
};

typedef struct Lyric_Font_Render_Prop_
{
	std::string _fontName;			//字体
	int _titleSize;					//歌名的字体大小
	int _infoSize;					//原唱等信息的字体大小
	int _lyricSize;					//歌词的字体大小
	int	_outlineWidth;				//描边的像素点
	int	_borderPixel;				//加粗的像素点数，一般1就可以了

} LYRIC_FONT_RENDER_PROP;


/* combine strings in precompile */
#define krk_cat2(i,j)       i##j
#define krk_cat3(i,j,k)     i##j##k

/* min&max */
#define krk_max2(a,b)	((a)>(b)?(a):(b))
#define krk_max3(a,b,c)	krk_max2(krk_max2(a,b),c)
#define krk_min2(a,b)	((a)<(b)?(a):(b))
#define krk_min3(a,b,c)	krk_min2(krk_min2(a,b),c)

/* word&dword swap */
#define krk_swap(a)	( ((a) << 4 & 0xf0) | ((a) >> 4 & 0x0f))
#define krk_swap2(a)	( ((((unsigned short)(a))&0xff)<<8) | ((((unsigned short)(a))&0xff00)>>8) )
#define krk_swap4(a)	( ((((unsigned long)(a))&0xff)<<24) | ((((unsigned long)(a))&0xff00)<<8) | \
			  				((((unsigned long)(a))&0xff0000)>>8) | ((((unsigned long)(a))&0xff000000)>>24) )
#define krk_swap2b4b(a)	( ((((unsigned long)(a))&0xff000000)>>8) | ((((unsigned long)(a))&0xff0000)<<8) | \
						  ((((unsigned long)(a))&0xff)<<8) | ((((unsigned long)(a))&0xff00)>>8) )

#define krk_exchange(p, q)	 do { \
								 unsigned char tmp_xxxx;\
								 tmp_xxxx = *(p);\
								 *(p) = *(q);\
								 *(q) = tmp_xxxx;\
							} while (0);

#define krk_trunk_val(min, max, val)	val = ((val)<(min))? (min) : (((val) > (max))? (max) : (val))

/* usefull macro for calc buffer pointer in cycle buffer */
#define krk_buf_distance(front_ptr, back_ptr, val, buf_size) do { \
    (val) = (front_ptr) - (back_ptr); \
    if ((val) < 0) (val) += (buf_size); \
} while (0)

#define krk_buf_inc_ptr(ptr, ndword, buf_end, buf_size) do {\
    (ptr) += (ndword); \
    if ((ptr) >= (buf_end)) (ptr) -= (buf_size); \
} while (0)

#define krk_buf_dec_ptr(ptr, ndword, buf_start, buf_size) do {\
    (ptr) -= (ndword); \
    if ((ptr) < (buf_start)) (ptr) += (buf_size); \
} while (0)

/* bytes stream to integer */
#define K_GETLONG_LSB(addr) ((((unsigned char *)(addr))[3]<<24)+(((unsigned char *)(addr))[2]<<16)+(((unsigned char *)(addr))[1]<<8)+(((unsigned char *)(addr))[0]<<0))
#define K_GETLONG_MSB(addr) ((((unsigned char *)(addr))[0]<<24)+(((unsigned char *)(addr))[1]<<16)+(((unsigned char *)(addr))[2]<<8)+(((unsigned char *)(addr))[3]<<0))
#define K_GETSHORT_LSB(addr) ((((unsigned char *)(addr))[1]<<8)+(((unsigned char *)(addr))[0]<<0))
#define K_GETSHORT_MSB(addr) ((((unsigned char *)(addr))[0]<<8)+(((unsigned char *)(addr))[1]<<0))

#define K_SETLONG_LSB(val, addr) {((unsigned char *)(addr))[0]=((val)&0xff); ((unsigned char *)(addr))[1]=((val)>>8)&0xff; ((unsigned char *)(addr))[2]=((val)>>16)&0xff; ((unsigned char *)(addr))[3]=((val)>>24)&0xff;}
#define K_SETLONG_MSB(val, addr) {((unsigned char *)(addr))[3]=((val)&0xff); ((unsigned char *)(addr))[2]=((val)>>8)&0xff; ((unsigned char *)(addr))[1]=((val)>>16)&0xff; ((unsigned char *)(addr))[0]=((val)>>24)&0xff;}
#define K_SETSHORT_LSB(val, addr) {((unsigned char *)(addr))[0]=((val)&0xff); ((unsigned char *)(addr))[1]=((val)>>8)&0xff;}
#define K_SETSHORT_MSB(val, addr) {((unsigned char *)(addr))[1]=((val)&0xff); ((unsigned char *)(addr))[0]=((val)>>8)&0xff;}

#define K_BCD2INT_MSB(pBCD) 	((unsigned)(*(pBCD) & 0xf)*10000+(unsigned)(*((pBCD)+1)>>4)*1000+(unsigned)(*((pBCD)+1) & 0xf)*100+(*((pBCD)+2)>>4)*10+(*((pBCD)+2)&0xf))
#define K_BCD2INT_LSB(pBCD)		((unsigned)(*(pBCD) >>4)*10+(unsigned)(*(pBCD) & 0xf)+(unsigned)(*((pBCD)+1)>>4)*1000+(unsigned)(*((pBCD)+1) & 0xf)*100+(unsigned)(*((pBCD)+2)&0xf)*10000)

#define KRK_BIG_ENDIAN		0
#define KRK_SMALL_ENDIAN 	1

#define K_SHORT_ENDIANCONVERT(arc_en, data_en, data) ((arc_en == KRK_BIG_ENDIAN) && (data_en == KRK_SMALL_ENDIAN))? K_GETSHORT_MSB(&(data)) : (((arc_en == KRK_SMALL_ENDIAN) && (data_en == KRK_BIG_ENDIAN))? K_GETSHORT_LSB(&(data)) : (data))
#define K_LONG_ENDIANCONVERT(arc_en, data_en, data) ((arc_en == KRK_BIG_ENDIAN) && (data_en == KRK_SMALL_ENDIAN))? K_GETLONG_MSB(&(data)) : (((arc_en == KRK_SMALL_ENDIAN) && (data_en == KRK_BIG_ENDIAN))? K_GETLONG_LSB(&(data)) : (data))


#endif
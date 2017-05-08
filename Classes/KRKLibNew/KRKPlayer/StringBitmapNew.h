#pragma once
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

extern "C"
{
#include <hb-ft.h>
}

#include "CommonDefine.h"
#include "Base/Ref.h"

#ifndef MIN
#define MIN krk_min2
#endif
#ifndef MAX
#define MAX krk_max2
#endif

//类主要处理对象
//非Unicode字符串和语言属性
//Unicode字符串
//UTF-8字符串

//类主要功能简介
//生成字符串的灰度图，Shader上色
//生成字符串的边框灰度图，Shader上色
//生成带颜色和边框的RGBA图，一般opengl的渲染不使用
//字符串每个字符的宽度
enum SB_RULE
{
	SB_RULE_NONE = 0,
	SB_RULE_SPACE = (1<<1),
	SB_RULE_MIDLINE = (1<<2),
	SB_RULE_EVERYCODE = (1<<3),
	SB_RULE_NK_BOLD = (1<<4),
	SB_RULE_FAKE_MULTI = (1<<5),			// fake multi-StringBitmapNew
};

union Pixel32
{
  Pixel32()
  : integer(0) { }
  Pixel32(unsigned char ri, unsigned char gi, unsigned char bi,unsigned char ai = 255)
  {
    b = bi;
    g = gi;
    r = ri;
    a = ai;
  }

  unsigned int integer;

  struct
  {
#ifdef BIG_ENDIAN
    unsigned char a, b, g, r;
#else // LITTER_ENDIAN
    unsigned char r, g, b, a;
#endif // BIG_ENDIAN
  };
};

struct FontVec2
{
  FontVec2() { }
  FontVec2(float a, float b)
  : x(a), y(b) { }

  float x, y;
};

struct BITMAP_Rect
{
  BITMAP_Rect() { }
  BITMAP_Rect(float left, float top, float right, float bottom)
  : xmin(left), xmax(right), ymin(top), ymax(bottom) { }

  void Include(const FontVec2 &r)
  {
    xmin = MIN(xmin, r.x);
    ymin = MIN(ymin, r.y);
    xmax = MAX(xmax, r.x);
    ymax = MAX(ymax, r.y);
  }

  float Width() const { return xmax - xmin + 1; }
  float Height() const { return ymax - ymin + 1; }

  float xmin, xmax, ymin, ymax;
};

struct Span
{
  Span() {x= 0;y = 0; width = 0;coverage = 0;}
  Span(int _x, int _y, int _width, int _coverage)
  : x(_x), y(_y), width(_width), coverage(_coverage) { }

  int x, y, width, coverage;
};
typedef std::vector<Span> Spans;

struct Pos
{
	Pos() { }

	Pos(int left, int top, int right, int bottom)
  : xmin(left), xmax(right), ymin(top), ymax(bottom) { }

	int xmin, xmax, ymin, ymax;
};


struct Hight_Width
{
	Hight_Width() { }

	Hight_Width(int get_hight, int get_width, int get_xmin, int get_ymin)
  : hight(get_hight), width(get_width), xmin(get_xmin), ymin(get_ymin){ }

	int hight, width;
	int xmin, ymin;
};

//	Pos_X() { }
//Pos_X(float left, float right)
//  : xmin(left), xmax(right){ }

typedef struct Pos_X_
{
	int xmin;
	int xmax;
} Pos_X;

#define MAX_GLYPH_COUNT		256

class StringBitmapNew : public Ref
{
public:
	StringBitmapNew(std::string _playerName, const char *_localeString, int _length, int _language, FT_Library _library, FT_Face _face, int _fontSize, float _borderPixel, int _outlineWidth, hb_font_t * _hb_font);
	StringBitmapNew(std::string _playerName, unsigned short *_unicodeString, int _length, FT_Library _library, FT_Face _face, int _fontSize, float _borderPixel, int _outlineWidth, hb_font_t * _hb_font);
	StringBitmapNew(std::string _playerName, char *_utf8String, int _length, FT_Library _library, FT_Face _face, int _fontSize, float _borderPixel, int _outlineWidth, hb_font_t * _hb_font);
	~StringBitmapNew();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string PlayerName;
	static	int ReferenceTimes;

	unsigned short	*UnicodeString;
	int			LocalStringCharNum;  //本地编码表示的字符个数
	int			UnicodeStringCharNum;  //本地编码表示的字符个数
	int			FontLanguageType;
	FT_Library	FTLibraryNow;
	FT_Face		FTFaceNow;
	hb_font_t * hb_fontNow;

	int			RenderPixel(int _fontSize, int _outLineWidth, int SplitRule, int WordSpace, float Borderpixel);		//灰度字
	void		WriteGlyphPixelAlpha();
	//void		WriteGlyphPixelColor(const Pixel32 &fontCol, const Pixel32 &outlineCol);
	int			CaculateLocalStringNum(unsigned char *LocalString, int Length, int Language);

	float		CaculateStringRenderPercent(int CurWord, int Percent);

	void		MatchGlyphAndInputString(); //Glyph和原始传进来的字符数组的大概对应关系

	void		GlyphSlot_Embolden(int* Borderpixel_Y, FT_GlyphSlot slot, float Borderpixel);
	void		RenderSpans(FT_Library library, FT_Outline * outline, Spans *spans);

	int			GetImageHeight() {return ImageHeight;};
	int			GetImageWidth() {return ImageWidth;};
	int			GetImageSize() {return ImageSize;};

	float		GetCurrentPercent() {return CurrentPercent;};
	float		GetAnchorY();

	unsigned char *GetPixelAlpha();
private:

	int			OutLineWidth;
	int			FontSize;
	int			GlyphLength;

	int			Y_Min;
	int			Y_Max;
	//void RenderBitmapColor(int FontSize);	//彩色字
	int			Borderpixel_Y[MAX_GLYPH_COUNT];

	Spans		SpansBaseInfo[MAX_GLYPH_COUNT];	 //字形轮廓信息
	Spans		SpansOutLine[MAX_GLYPH_COUNT];	 //字形轮廓信息

	
	Pos			PositionOut[MAX_GLYPH_COUNT];
	int			GlyphWidth[MAX_GLYPH_COUNT];
	Pos_X		GlyphHori[MAX_GLYPH_COUNT];
	Pos_X		SpaceSplit[MAX_GLYPH_COUNT];
	int			SpacePos[MAX_GLYPH_COUNT];

	Pos_X		GlyphHoriNew[MAX_GLYPH_COUNT];
	Pos_X		SpaceSplitNew[MAX_GLYPH_COUNT];

	int			ImageHeight;
	int			ImageWidth;
	int			ImageSize;
	unsigned char *PixelBaseAlpha;
	//unsigned char *PixelOutLineAlpha;
	//unsigned char *PixelColor;

	float		CurrentPercent;		//当前染色百分比0.0-1.0
	int			NowX_Max;			//当前刷到的X宽度
	//int			PostionAnchorY;
	//float	    AnchorY;
	int			IsGenerated;
};
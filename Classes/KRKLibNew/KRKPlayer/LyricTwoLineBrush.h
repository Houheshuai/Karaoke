#ifndef LYRIC_OB_TWO_LINE_H
#define LYRIC_OB_TWO_LINE_H

#include <string>

#include "KaraokePaintingBrush.h"
#include "StringBitmapNew.h"
#include "CommonDefine.h"

#include "Renderer/Layer.h"

#include "Renderer/SpecialFunctionCharCache.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

extern "C"
{
#include <hb-ft.h>
}

//更新歌词
//更新Bitmap
//通知画图
//针对两行歌词渲染
//生成Bitmap
#define MAX_LYRIC_CACHE_LINES	3
#define LYRIC_LINES				2
#define MAX_SONG_INFO_LINES		6
#define MAX_TIPS_NUM			4

class LyricTwoLineBrush:public KaraokePaintingBrush
{
public:
	LyricTwoLineBrush(std::string _className);
	~LyricTwoLineBrush();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;

	void Update(void *_krkPlayer);		
	void Draw(void *_karaokeSurface);
	void Reset();

private:
	void ClearSprite();
	void DealWithLyricLine(int index, void *_lyricLineInfo, void *_krkPlayer, int Languange);

	//Reset需要重置的
	StringBitmapNew	*SongInfoBitmap[MAX_SONG_INFO_LINES];
	int				LineNumber[LYRIC_LINES];
	StringBitmapNew	*LyricBitmap[LYRIC_LINES][MAX_LYRIC_CACHE_LINES];
	int				LyricPosWrite[LYRIC_LINES];
	int				LyricPosRead[LYRIC_LINES];

	Sprite			*LastSongInfoSprite[MAX_SONG_INFO_LINES];
	Sprite			*LastLyricInSprite[LYRIC_LINES];
	//越南客户MTV喜欢所有的字后面有一层黑色阴影
	Sprite			*LastLyricInSpriteShadow[LYRIC_LINES];
	Sprite			*LastLyricOutSprite[LYRIC_LINES];
	Sprite			*LastTipsSprite[MAX_TIPS_NUM];

	int				TipsIndex;
	int				LastTipsIndex;
	int				TipsColorReady;

	//Lyric相关信息
	enum LYRIC_ANIMATION
	{
		LYRIC_ANIMATION_NONE,				//没有歌词
		LYRIC_ANIMATION_BRUSH_START,		//开始染色
		LYRIC_ANIMATION_BRUSH_END,			//结束染色
		LYRIC_ANIMATION_CHANGE,				//开始入场显示

		LYRIC_ANIMATION_CHANGE_DEALEND,
	};
	enum LYRIC_ANIMATION LyricAnimationFlag[LYRIC_LINES];	//
	float LyricAnimationPercent[LYRIC_LINES];				//一般表示刷字百分比
	Vec4 LyricColorBrush[LYRIC_LINES];
	Vec4 LyricColorBase[LYRIC_LINES];
	Vec4 LyricColorOutLineBrush[LYRIC_LINES];
	Vec4 LyricColorOutLineBase[LYRIC_LINES];
	//Reset需要重置的

	//int			SpritePosWrite[LYRIC_LINES];
	//int			SpritePosRead[LYRIC_LINES];

	LYRIC_FONT_RENDER_PROP	LyricPropSave;

	FT_Library		FTLibrary_Cache;
	FT_Face			FTFace_Cache;
	hb_font_t *		HB_Font_Cache;


	int				NextShowStatus;
	int				ShowStatusNow;
	int				AfterReset;

	SpecialFunctionCharCache *_specialCharCache;

	Layer *karaokeSurface;

};

#endif
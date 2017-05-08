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

//���¸��
//����Bitmap
//֪ͨ��ͼ
//������и����Ⱦ
//����Bitmap
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

	//Reset��Ҫ���õ�
	StringBitmapNew	*SongInfoBitmap[MAX_SONG_INFO_LINES];
	int				LineNumber[LYRIC_LINES];
	StringBitmapNew	*LyricBitmap[LYRIC_LINES][MAX_LYRIC_CACHE_LINES];
	int				LyricPosWrite[LYRIC_LINES];
	int				LyricPosRead[LYRIC_LINES];

	Sprite			*LastSongInfoSprite[MAX_SONG_INFO_LINES];
	Sprite			*LastLyricInSprite[LYRIC_LINES];
	//Խ�Ͽͻ�MTVϲ�����е��ֺ�����һ���ɫ��Ӱ
	Sprite			*LastLyricInSpriteShadow[LYRIC_LINES];
	Sprite			*LastLyricOutSprite[LYRIC_LINES];
	Sprite			*LastTipsSprite[MAX_TIPS_NUM];

	int				TipsIndex;
	int				LastTipsIndex;
	int				TipsColorReady;

	//Lyric�����Ϣ
	enum LYRIC_ANIMATION
	{
		LYRIC_ANIMATION_NONE,				//û�и��
		LYRIC_ANIMATION_BRUSH_START,		//��ʼȾɫ
		LYRIC_ANIMATION_BRUSH_END,			//����Ⱦɫ
		LYRIC_ANIMATION_CHANGE,				//��ʼ�볡��ʾ

		LYRIC_ANIMATION_CHANGE_DEALEND,
	};
	enum LYRIC_ANIMATION LyricAnimationFlag[LYRIC_LINES];	//
	float LyricAnimationPercent[LYRIC_LINES];				//һ���ʾˢ�ְٷֱ�
	Vec4 LyricColorBrush[LYRIC_LINES];
	Vec4 LyricColorBase[LYRIC_LINES];
	Vec4 LyricColorOutLineBrush[LYRIC_LINES];
	Vec4 LyricColorOutLineBase[LYRIC_LINES];
	//Reset��Ҫ���õ�

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
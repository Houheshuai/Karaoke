#ifndef BLANK_BRUSH_H
#define BLANK_BRUSH_H

#include <string>

#include "KaraokePaintingBrush.h"
#include "CommonDefine.h"
#include "Renderer/Layer.h"

class BlankBrush:public KaraokePaintingBrush
{
public:
	BlankBrush(std::string _className);
	~BlankBrush();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;

	void Update(void *_krkPlayer);		
	void Draw(void *_karaokeSurface);
	void Reset();

private:
	void ClearSprite();
	
	int				NextShowStatus;
	int				ShowStatusNow;
	int				AfterReset;
	Layer *karaokeSurface;

};

#endif
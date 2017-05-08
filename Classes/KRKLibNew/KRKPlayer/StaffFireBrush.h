#ifndef STAFF_FIRE_BRUSH_H
#define STAFF_FIRE_BRUSH_H

#include <string>

#include "KaraokePaintingBrush.h"
#include "CommonDefine.h"
#include "Renderer/Layer.h"
#include "Renderer/SpecialFunctionCharCache.h"


class StaffFireBrush:public KaraokePaintingBrush
{
public:
	StaffFireBrush(std::string _className);
	~StaffFireBrush();

	void SetLog(int _logFlag);

	int			LogFlag;
	std::string MyClassName;
	static	int ReferenceTimes;

	void Update(void *_krkPlayer);		
	void Draw(void *_karaokeSurface);
	void Reset();

private:
	void ClearSprite();
	
	int	NextShowStatus;
	int	ShowStatusNow;
	int	AfterReset;
	Layer *karaokeSurface;

};

#endif
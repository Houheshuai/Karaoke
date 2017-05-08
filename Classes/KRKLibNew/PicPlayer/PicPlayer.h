#pragma once
#include <vector>
#include <string>
#include "InterfacePicPlayer.h"
#include "Renderer/Sprite.h"
#include "Platform/Image.h"
#include "Effects/NodeGrid.h"


//class CrippleSprite;
class Sprite;
//class MeshSprite;
class Image;
class NodeGrid;
class PicPlayer:public InterfacePicPlayer
{
public:
	const static int	Max_Camera_Area = 4;

	PicPlayer(std::string _playerName);
	~PicPlayer();

	int Draw(float _deltaSecs);
	int AddPictureFile(std::string _picPath);
	void AddPictureInfo(int _index, int x, int y, int w, int h, int angle, float scale);

	//初始化带位置信息的图片

	int SetPlayIndex(int _picIndex);
	int SetCameraIndex(int _camIndex);

	//叠加摄像头图片开关
	int TurnOnCameraOverride(int w, int h);
	int TurnOffCameraOverride();

	void ShowPictureFile(std::string _picPath);

	void SetCameraOverrideEnable(bool enabled);
	
	int AddCameraFile(std::string _camPath);
	int AddCameraBuffer(unsigned char *_camBuff, int _size);

	static void *LoadImageData(void *_param);
	//static void *EndGridAction(void *_param);

	void StopActionGrid();

	int				_nextPlayIndex;
	int				_nextCameraIndex;
	Image			*_picCache;
	Image			*_cameraCache[Max_Camera_Area];
	int				_cameraCacheIndex;

private:
	void ClearSprite();

	int RunActionInOut(Sprite *_NodeOut, Sprite *_NodeIn);

	static int ReferenceTimes;
	std::string PlayerName;
	int			LogFlag;

	typedef struct _PicInfo
	{
		std::string _picPath;
		Rect		_area[Max_Camera_Area];
		int			_rotateAngle[Max_Camera_Area];            //顺时针为正，度数衡量
		int		    _areaCount;
	} PICINFO;

	std::vector<PICINFO>		_picFiles;
	

	std::vector<std::string>	_cameraFiles;

	int _currentPlayIndex;
	int _currentCameraIndex;

	
	Sprite    *PicInNode;
	Sprite    *PicOutNode;

	NodeGrid	*InProxy;
	NodeGrid	*OutProxy;

	int		IsNeedProxyIn;
	int		IsNeedProxyOut;
	//Sprite	*PicInSprite;
	//Sprite	*PicOutSprite;
	//Sprite	*CameraSpriteIn[Max_Camera_Area];
	//Sprite	*CameraSpriteOut[Max_Camera_Area];

	bool	CameraOverrideEnable;
};
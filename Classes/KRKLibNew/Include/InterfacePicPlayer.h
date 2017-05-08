#ifndef _INTERFACE_PIC_H
#define _INTERFACE_PIC_H
#include <string>

class InterfacePicPlayer
{
public:
	virtual ~InterfacePicPlayer(){};

	virtual int Draw(float _deltaSecs) = 0;

	virtual int AddPictureFile(std::string _picPath) = 0;
	virtual void AddPictureInfo(int _index, int x, int y, int w, int h, int angle, float scale) = 0;
	virtual int SetPlayIndex(int _picIndex) = 0;

	virtual int AddCameraFile(std::string _camPath) = 0;
	virtual int AddCameraBuffer(unsigned char *_camBuff, int _size) = 0;
	virtual int SetCameraIndex(int _camIndex) = 0;

	//
	virtual int TurnOnCameraOverride(int w, int h) = 0;
	virtual int TurnOffCameraOverride() = 0;

	virtual void ShowPictureFile(std::string _picPath) = 0;
};

extern "C" void CreatePicPlayer(InterfacePicPlayer *&_picPlayer, std::string PlayerName);

extern "C" void DestroyPicPlayer(InterfacePicPlayer *_picPlayer);


#endif

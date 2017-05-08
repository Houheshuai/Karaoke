#ifndef _GAMETEXTURE_H
#define _GAMETEXTURE_H

#include "Renderer/OpenGLESHeaders.h"
#include "CStringBitmap.h"
#include "CEGUI/CEGUIVector.h"
#include <unordered_map>

class Sprite;
class Image;
class SpriteAuto;
class CGameTexture
{
public:
	CGameTexture(const char* _fileName);
	CGameTexture(unsigned char *bitmap, int w, int h, int rebMode);
	CGameTexture(Image *img);
	//CGameTexture(StringBitmap& strBitmap);
	//CGameTexture(StringBitmap* strBitmap);
	CGameTexture(StringBitmap_t* strBitmap);
	//CGameTexture(int textureID, int texWidth, int texHeight, const GLvoid *data);
	void RemoveChildByResID(long ResID);
	void AddChildByResID(long ResID, float x, float y, float w, float h);
	Sprite *GetChildByResID(long ResID);

	void RunActionByResID(long ResID, int ActionType);

	static SpriteAuto *CreateFromBuffer(unsigned char *bitmap, int w, int h, int rebMode);
	void FadeOutGameTexture(long resID, float time);

	void DeleGameTexture();

public:
	virtual ~CGameTexture(void);
	void SetStateBind();
	int GetWidth(void);
	int GetHeight(void);
	int GetTexID(void);

	GLuint			m_uiTexture;
	GLuint			m_uiTexture2;
	int				m_format;
	//Pixel32			m_color;
	//Pixel32			m_color2;

private:
	std::string		fileName;
	int				width;
	int				height;
	bool			fileFlag;//是否是通过load纹理来创建的对象

	int				VectorNum;

	std::unordered_map<long, Sprite*> m_SpriteList;
	//std::unordered_map<CEGUI::Vector2, int> m_SpriteVector;
};
#endif


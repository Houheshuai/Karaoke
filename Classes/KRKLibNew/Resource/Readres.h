#ifndef _READRES_
#define _READRES_

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif

#include "Resource/Resource.h"
#include <map>
#include "GUIBase/M3D_Singleton.h"
#include "CEGUI/CEGUIString.h"
#include "CEGUI/CEGUIVector.h"

namespace CEGUI
{
#define MAXIMGFILENUM 500

class Vector2;
class CEGUIString;
typedef struct 
{
	char    Vendor[8];
	char    Producer[8];
	char    Revision[8];
	uint    HeadSize;
	char    Reserved[8];
	uint    StringListOffset;
	uint    StyleListOffset;
	uint    ImageListOffset;
	uint    WndListOffset;
	uint    ActionListOffset;
} FileHead_t;


typedef struct ImageFileTextureMap
{
	int ImageFileID;
	void *imgTexture;
}ImageFileTextureMap_t;

//! texture cover coordinate
typedef struct{
	Vector2 left_down_tx;
	Vector2 right_down_tx;
	Vector2 left_up_tx;
	Vector2 right_up_tx;		
}GDI_TEXTURE_COVER_t;

typedef struct	ResImageTexture
{
	void *imgTexture;
	int refcount;
	GDI_TEXTURE_COVER_t CoverTexPara;
} ResImageTexture_t;

class ReadRes : public M3D_Singleton <ReadRes>
{
public:
	ReadRes(void);
	~ReadRes(void);	 

	bool GetAction(uint ActionID, ActionRes_t& actRes);

	StyleProperty_t *GetStyle(uint styleID);

	std::string GetString(uint stringID);

	ImageFile_t *GetImageFile(uint ImageFileID);

	ImageData_t *GetImage(uint ImageID);

	void *GetImageFileTexture(uint ImageFileID);

	bool LoadALLImageFile(void);
	void ReleaseALLImageFile(void);

	ResImageTexture_t& GetImageTexture(uint ImageID);
	int ReleaseImageTexture(uint ImageID);

	void CacheClean(void);

	WndRes_t *getNextBrother(WndRes_t *pwnd);

	WndRes_t *GetWndRes(uint WndID);

	WndRes_t *GetWndList(void);

	WndRes_t *GetWndRes(WndRes_t *Parent, uint Id);

	int LoadRes(const String fname, const String resFolder);

	void CloseRes();
	
private:
	
	typedef std::map<uint, ResImageTexture_t> TextureCachePool;
	
 	TextureCachePool d_TextureCachePool;
	ImageFileTextureMap_t ImageFileTexture[MAXIMGFILENUM];
	
	FileHead_t			 d_FileHead;
	StringList_t		 d_StringList;
	StyleList_t 		 d_StyleList;
	ImageList_t 		 d_imageList;
	WndList_t			 d_WndList;
	ActionList_t		 d_ActionList;

	ResImageTexture_t    d_dummyTexture;

	//vector<String>	v_Res_Strings;
	//char				m_currentString[200];
	int					d_ResFlag;

	std::string			d_resRootFolderPath;
};

}

#endif

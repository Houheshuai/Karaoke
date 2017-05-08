#ifndef _GUI_RESOURCE_H_
#define _GUI_RESOURCE_H_

#define WND_NAME_SZ		32
#define WND_RES_DATA_COUNT 12
#define IMAGE_FILENAME_SZ 64
#define RES_PATH_MAX_SZ		256

/*
*	string resource
*/
typedef struct
{
    unsigned int        StringID;
    unsigned int        Stringoffset;  
}ResStringOffset_t;

typedef struct 
{

   unsigned int     StringCount;		
   unsigned int     StringSize;			
   unsigned int     TableDataLen;	
   ResStringOffset_t*    pStringOffset;
   unsigned short 	*pStringData;
} ResStringList_t;

/*
*	image resource
*/
typedef struct
{
   unsigned int    ImageFileID;
   char    ImageFileName[IMAGE_FILENAME_SZ];
}ResImageFile_t;

typedef struct
{
   unsigned int    ImageID;
   unsigned int    ImageFileID;
   float   ImageStarX;  
   float   ImageStarY;
   float   ImageWidth;
   float   ImageHeight;  
}ResImageData_t;

typedef struct
{
   unsigned int         ImageFileCount;
   unsigned int         ImageCount;
   unsigned int         ImageSize;
   ResImageFile_t* pImageName;	
   ResImageData_t* pImageData;
}ResImageList_t;

/*
*	action resource
*/
typedef struct
{
    unsigned int        ActionID;
    unsigned int        ActionTableoffset;
}ResActionOffset_t;

 typedef struct 
{
   unsigned int  LTopX;
   unsigned int  LTopY;
   unsigned int  RTopX;
   unsigned int  RTopY;
   unsigned int  RBottomX;
   unsigned int  RBottomY;
   unsigned int  LBottomX;
   unsigned int  LBottomY;
   float  alpha;
}ResCoordProperty_t;

typedef struct 
{
   unsigned int             Dotcount;
   unsigned int             FrameCount;
   unsigned int            FrameRate;
   int              ResolutWidth;
   int              ResolutHeight;
}ResActionData_t;

typedef struct 
{
   unsigned int        ActionCount;
   unsigned int 	   Actionsize;
   unsigned int 	   TableDataLen;	
   ResActionOffset_t*  pActionOffset;
   ResActionData_t*   pActionData;
   ResCoordProperty_t* pCoordPro;
}ResActionList_t;

typedef struct 
{
	ResActionData_t*	pActionData;
	ResCoordProperty_t* pCoordPro;
} ResAction_t;

/*
*	style resource
*/
typedef struct 
{
   unsigned int   StringStyleID;
   unsigned int   frontcolor;
   unsigned int   framecolor;
   unsigned int    FontSize;
   unsigned int    aligned;
}ResStyleProperty_t;

typedef struct 
{
   unsigned int   StyleCount;
   unsigned int   StyleSize;
   ResStyleProperty_t* pStylePro;
}ResStyleList_t;

/*
*	window resource
*/
typedef struct
{
    unsigned int        RootWndID;
    unsigned int        RootWndoffset;  
}ResRootWndOffset_t;

typedef struct 
{
	char Name[WND_NAME_SZ];
	unsigned int   WndID;
	unsigned int   ParWndID;
   unsigned int   classID; //classID
   unsigned int   ChildCount;
   float  startX;
   float  startY;
   float  width;
   float  height;
   float  alpha;
   unsigned int   reserved[WND_RES_DATA_COUNT];
   
   // wnd基类属性
} ResWndBase_t;

typedef struct 
{
   
   unsigned int StringID;
   unsigned int StringStyleID;
   
	   // StringLabel属性
} ResStringLabel_t;

typedef struct
{
  
   unsigned int ImageID;
   // ImageLabel属性
} ResImageLabel_t;

typedef struct
{
    ResWndBase_t WndBase;
    ResStringLabel_t StringRes;
    ResImageLabel_t ImageRes;    
} ResWnd_t;

typedef struct 
{
   unsigned int      RootWndCount;
   unsigned int      WndCount;
   unsigned int      RootWndSize;
   ResRootWndOffset_t *pRootWndTableOffset;
   ResWnd_t* pWndRes;
   //unsigned int*     pWndChild;
}ResWndList_t;

typedef struct 
{
	char    Vendor[8];
	char    Producer[8];
	char    Revision[8];
	unsigned int    HeadSize;
	char		StringCodePage;
	char    Reserved[7];
	unsigned int    StringListOffset;
	unsigned int    StyleListOffset;
	unsigned int    ImageListOffset;
	unsigned int    WndListOffset;
	unsigned int    ActionListOffset;
} ResFileHead_t;

typedef struct s_GuiResource
{
	ResFileHead_t 	d_FileHead;
	ResStringList_t 	 d_StringList;
	ResStyleList_t		 d_StyleList;
	ResImageList_t		 d_imageList;
	ResWndList_t		 d_WndList;
	ResActionList_t 	 d_ActionList;

	gdi_texture_t* d_imgFileTexture;
	gdi_texture_t* d_imgTexture;

	int 					d_loadAll;
	char					d_resPath[RES_PATH_MAX_SZ];
	int*					d_cache;
} ezResource_t;

typedef struct 
{
	unsigned int bgColor;
	unsigned int frontColor;
	unsigned int borderColor1;
	unsigned int borderColor2;
	
} GuiWidgetStyle_t;

#ifdef __cplusplus
extern "C" {
#endif

extern char *res_getString(ezResource_t* res, unsigned int stringID, char* out_str, int maxlen);

extern ResStyleProperty_t *res_getStyle(ezResource_t* res, unsigned int styleID);

extern ResImageFile_t *res_getImageFile(ezResource_t* res, unsigned int ImageFileID);

extern ResImageData_t *res_getImage(ezResource_t* res, unsigned int ImageID);

extern void res_unloadAllImageTexture(ezResource_t* res);

extern int res_loadAllImageTexture(ezResource_t* res);

extern gdi_texture_t *res_getImageFileTexture(ezResource_t* res, unsigned int ImageFileID);

extern gdi_texture_t* res_getImageTexture(ezResource_t* res, unsigned int ImageID);

extern void res_releaseImageTexture(ezResource_t* res, gdi_texture_t* texture);

extern ResWnd_t *res_getWndRes(ezResource_t* res, ResWnd_t *parent, unsigned int Id);

extern int res_getFormCount(ezResource_t* res);

extern int res_getAction(ezResource_t* res, unsigned int ActionID, ResAction_t* actRes);

extern void res_unloadResFile(ezResource_t* res );

extern int res_loadResFile(const char* fname, ezResource_t* res);

/*
 * Function name  	: res_loadResources
 * Arguments      	: appName - GUI application name
 *									loadAllRes - read all res to memory
 * Return         	: GUI resources handle
 * Description    	: load resource data from resource file, resource file name is "AppName.res"
 *					
*/
extern ezResource_t * res_loadResources(const char *appName, int loadAllRes);

/*
 * Function name  	: res_unloadResources
 * Arguments      	: pRes - resource handle
 * Return         	: none
 * Description    	: free resource file buffer
 *					
*/
extern void res_unloadResources(ezResource_t *pRes);

/*
 * Function name  	: res_getResource
 * Arguments      	: res - gui res handle,  widgetID - control unique ID
 * Return         	: control resource data address
 * Description    	: get resource data of control from resource file, search by control ID
 *					
*/
extern ResWnd_t* res_getResource(ezResource_t* res, ResWnd_t *parent, unsigned int Id);

extern ResWnd_t* res_loadWndImageTextures(ezResource_t* res, ResWnd_t *parent, unsigned int WndId);

#ifdef __cplusplus
}
#endif

#endif


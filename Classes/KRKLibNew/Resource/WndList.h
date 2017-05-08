#ifndef _WND_LIST_
#define _WND_LIST_

#include "TypeDef.h"

typedef struct
{
    uint        RootWndID;
    uint        RootWndoffset;  
}RootWndTableOffset_t;

#define WND_NAME_SZ		32
#define WND_RES_DATA_COUNT 12

typedef struct 
{
	char Name[WND_NAME_SZ];
	uint   WndID;
	uint   ParWndID;
   uint   classID; //classID
   uint   ChildCount;
   float  startX;
   float  startY;
   float  width;
   float  height;
   float  alpha;
   uint   reserved[WND_RES_DATA_COUNT];
   
   // wnd基类属性
} WndBase_t;

typedef struct 
{
   
   uint StringID;
   uint StringStyleID;
   
	   // StringLabel属性
} StringLabel_t;

typedef struct
{
  
   uint ImageID;
   // ImageLabel属性
} ImageLabel_t;

typedef struct
{
    WndBase_t WndBase;
    StringLabel_t StringRes;
    ImageLabel_t ImageRes;    
} WndRes_t;

typedef struct 
{
   uint      RootWndCount;
   uint      WndCount;
   uint      RootWndSize;
   RootWndTableOffset_t *pRootWndTableOffset;
   WndRes_t* pWndRes;
   //uint*     pWndChild;
}WndList_t;

typedef struct
{
    uint      RootWndCount;
    uint      WndCount;
    uint      RootWndSize;
    uint      pRootWndTableOffset;
    uint      pWndRes;
    //uint*     pWndChild;
}WndList_t_File;

#endif

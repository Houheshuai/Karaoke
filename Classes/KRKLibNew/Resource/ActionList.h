#ifndef _ACTION_LIST_
#define _ACTION_LIST_

#include "TypeDef.h"

typedef struct
{
    uint        ActionID;
    uint        ActionTableoffset;
}ActionTableOffset_t;

 typedef struct 
{
   float  LTopX;
   float  LTopY;
   float  RTopX;
   float  RTopY;
   float  RBottomX;
   float  RBottomY;
   float  LBottomX;
   float  LBottomY;
   float  alpha;
}CoordProperty_t;

typedef struct 
{
   uint             Dotcount;
   uint             FrameCount;
   float            FrameRate;
   int              ResolutWidth;
   int              ResolutHeight;
}ActionData_t;

typedef struct 
{
   uint        ActionCount;
   uint 	   Actionsize;
   uint 	   TableDataLen;	
   ActionTableOffset_t*  pActionOffset;
   ActionData_t*   pActionData;
   CoordProperty_t* pCoordPro;
}ActionList_t;

typedef struct 
{
	ActionData_t*	pActionData;
	CoordProperty_t* pCoordPro;
} ActionRes_t;

typedef struct
{
    uint        ActionCount;
    uint 	   Actionsize;
    uint 	   TableDataLen;
    uint		   pActionOffset;
    uint		   pActionData;
    uint		   pCoordPro;
}ActionList_t_File;

typedef struct
{
    uint		   pActionData;
    uint		   pCoordPro;
} ActionRes_t_File;

#endif

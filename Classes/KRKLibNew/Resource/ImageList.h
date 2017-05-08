#ifndef _IMAGE_LIST_
#define _IMAGE_LIST_

#include "TypeDef.h"

#define MAX_SELECT_STR_LEN 64
typedef struct
{
   uint    ImageFileID;
   char    ImageFileName[MAX_SELECT_STR_LEN];
}ImageFile_t;

typedef struct
{
   uint    ImageID;
   uint    ImageFileID;
   float   ImageStarX;  
   float   ImageStarY;
   float   ImageWidth;
   float   ImageHeight;  
}ImageData_t;

typedef struct
{
   uint         ImageFileCount;
   uint         ImageCount;
   uint         ImageSize;
   ImageFile_t* pImageName;	
   ImageData_t* pImageData;
}ImageList_t;

typedef struct
{
    uint         ImageFileCount;
    uint         ImageCount;
    uint         ImageSize;
    uint         pImageName;
    uint         pImageData;
}ImageList_t_File;

#endif
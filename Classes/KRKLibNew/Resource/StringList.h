#ifndef _STRING_LIST_
#define _STRING_LIST_

#include "TypeDef.h"

//#define RES_UNICODE

typedef struct
{
    uint        StringID;
    uint        Stringoffset;  
}StringTableOffset_t;

typedef struct 
{

   uint     StringCount;		
   uint     StringSize;			
   uint     TableDataLen;	
   StringTableOffset_t*    pStringOffset;
#ifdef RES_UNICODE
   unsigned short 	*pStringData;			// unicode 
#else
   char 	*pStringData;			// utf8
#endif
} StringList_t;

typedef struct
{

    uint     StringCount;
    uint     StringSize;
    uint     TableDataLen;
    uint     pStringOffset;
#ifdef RES_UNICODE
    uint     pStringData;			// unicode
#else
    uint     pStringData;			// utf8
#endif
} StringList_t_File;

#endif
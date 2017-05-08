#ifndef _STYLE_LIST_
#define _STYLE_LIST_


#include "TypeDef.h"

typedef struct 
{
   uint   StringStyleID;
   uint   frontcolor;
   uint   framecolor;
   uint    FontSize;
   uint    aligned;
}StyleProperty_t;

typedef struct 
{
   uint   StyleCount;
   uint   StyleSize;
   StyleProperty_t* pStylePro;
}StyleList_t;

typedef struct
{
    uint   StyleCount;
    uint   StyleSize;
    uint   pStylePro;
}StyleList_t_File;

#endif

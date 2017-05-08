#ifndef _GUI_ENUMS_H_
#define _GUI_ENUMS_H_

typedef enum
{
	BD_TYPE_CHAR = 0xC001,
	BD_TYPE_SHORT,	
	BD_TYPE_INT,			
	BD_TYPE_FLOAT,		
	BD_TYPE_DOUBLE,	
	BD_TYPE_STRING,		
	BD_TYPE_WSTRING,	
	BD_TYPE_RECORD		
} bundingFieldType_et;

enum
{
	LOAD_RES_ONDRAW = 0,				// load res when draw widget
	LOAD_RES_ONCREATE,					// load res when create widget
	LOAD_RES_ALL,									// load all res when create app
	
};

#endif


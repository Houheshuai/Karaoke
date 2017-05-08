/*
** make a GUI application easy and clear							
**
** Filename : GuiString.h
**																	
** Description: basic string parse and render api
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
*/

#ifndef _GUI_STRING_H_
#define _GUI_STRING_H_

typedef struct 
{
	char*							string;
	unsigned int				bufSize;
	gdi_rect_t					bgArea;
	gdi_string_t					gdiString;
	int								layer;
	
} ezString_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: ez_resetString
 * Arguments      	: ezstr - input string handle
 * Return         	: none
 * Description    	: reset string handle context
 *					
*/
extern void ez_resetString(ezString_t* ezstr);

/*
 * Function name  	: ez_initString
 * Arguments      	: string - input string
 *								: ezstr - input string handle
 * Return         	: 0 ->succ, -1 ->error 
 * Description    	: init string
 *					
*/
extern int ez_initString(ezString_t* ezstr, char* string);

/*
 * Function name  	: ez_loadString
 * Arguments      	: string - input string
 *								: ezstr - input string handle
 * Return         	: 0 ->succ, -1 ->error 
 * Description    	: load string 
 *					
*/
extern int ez_loadString(ezString_t* ezstr, char* string);

/*
 * Function name  	: ez_reloadString
 * Arguments      	: ezstr - input string handle
 * Return         	: 0 ->succ, -1 ->error 
 * Description    	: reload string 
 *					
*/
extern int ez_reloadString(ezString_t* ezstr);

/*
 * Function name  	: ez_unloadString
 * Arguments      	: ezstr - string handle
 * Return         	: none
 * Description    	: free string texture
 *					
*/
extern void ez_unloadString(ezString_t* ezstr);

/*
 * Function name  	: ez_releaseString
 * Arguments      	: ezstr - string handle
 * Return         	: none
 * Description    	: release string 
 *					
*/
extern void ez_releaseString(ezString_t* ezstr);

/*
 * Function name  	: ez_setString
 * Arguments      	: ezstr - string handle
 *								: newStr - new string
 * Return         	: none
 * Description    	: set new string 
 *					
*/
extern void ez_setString(ezString_t* ezstr, char* newStr);

/*
 * Function name  	: ez_appendString
 * Arguments      	: ezstr - string handle
 *								: newStr - new string
 * Return         	: none
 * Description    	: append a new string to the end of old
 *					
*/
extern void ez_appendString(ezString_t* ezstr, char* newStr);

/*
 * Function name  	: ez_setStringStyle
 * Arguments      	: ezstr - string handle
 *								: pStyle - string style data
 * Return         	: none
 * Description    	: set string style
 *					
*/
extern void ez_setStringStyle(ezString_t* ezstr, void *pStyle);

/*
 * Function name  	: ez_setStringTrape
 * Arguments      	: ezstr - string handle
 *								: area - input display rect
 * Return         	: none
 * Description    	: set string display area
 *					
*/
extern void ez_setStringArea(ezString_t* ezstr, gdi_rect_t *area);
extern void ez_setStringWCutModulus(ezString_t* ezstr, float wCutModulusStart, float wCutModulusEnd);

/*
 * Function name  	: ez_setStringLength
 * Arguments      	: ezstr - string handle
 *								: bewLen - new length
 * Return         	: none
 * Description    	: set string length, if new length is bigger than old, memory will remalloc
 *					
*/
extern void ez_setStringLength(ezString_t* ezstr, unsigned int newLen);

/*
 * Function name  	: ez_drawString
 * Arguments      	: ezstr - string handle
 * Return         	: none
 * Description    	: draw string 
 *					
*/
extern void ez_drawString(ezString_t* ezstr);

#ifdef __cplusplus
}
#endif 

#endif



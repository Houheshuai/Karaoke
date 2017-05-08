/*
** make a GUI application easy and clear							
**
** Filename : GuiImage.h
**																	
** Description: basic image parse and render api
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
*/

#ifndef _GUI_IMAGE_H_
#define _GUI_IMAGE_H_

#include <gui/iapi/GuiRes.h>

typedef struct 
{
	unsigned int 		id;
	int						layer;
	gdi_texture_t*		imgTex;
	char*					path;
	gdi_rect_t			area;
	Trape4					bgTrape;
	float 					alpha;
	ezResource_t*	res;
} ezImage_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: ez_unloadImage
 * Arguments      	: image - image handle
 * Return         	: none
 * Description    	: unload image texture
 *					
*/
extern void ez_unloadImage(ezImage_t* image);

/*
 * Function name  	: ez_reloadImage
 * Arguments      	: image - image handle
 * Return         	: 0 - succ, <>0 err code
 * Description    	: reload image texture by id or path
 *					
*/
extern int ez_reloadImage(ezImage_t* image);

/*
 * Function name  	: ez_setImageArea
 * Arguments      	: image - image handle
 *								: area - image area in background window
 * Return         	: none
 * Description    	: set image area in background window
 *					
*/
extern void ez_setImageArea(ezImage_t* image, gdi_rect_t* area);

/*
 * Function name  	: ez_setImageTrape
 * Arguments      	: image - image handle
 *								: bgTrape - image trape on screen
 * Return         	: none
 * Description    	: set image trape on screen
 *					
*/
extern void ez_setImageTrape(ezImage_t* image, Trape4* bgTrape);

/*
 * Function name  	: ez_initImageFromRes
 * Arguments      	: imgResId - image resource ID
 * Return         	: image handle
 * Description    	: init image by resource id
 *					
*/
extern ezImage_t* ez_initImageFromRes(ezResource_t* res, unsigned int imgResId);

/*
 * Function name  	: ez_loadImageFromRes
 * Arguments      	: res - gui res file handle, imgResId - image resource ID
 * Return         	: image handle
 * Description    	: load image 
 *					
*/
extern ezImage_t* ez_loadImageFromRes(ezResource_t* res, unsigned int imgResId);

/*
 * Function name  	: ez_loadImageFromRes
 * Arguments      	: filePath - image file path
 * Return         	: image handle
 * Description    	: load image 
 *					
*/
extern ezImage_t* ez_loadImageFromFile(const char* filePath);

/*
 * Function name  	: ez_releaseImage
 * Arguments      	: image - image handle
 * Return         	: none
 * Description    	: release image 
 *					
*/
extern ezImage_t* ez_createImage(int layer, int width, int height);

/*
 * Function name  	: ez_releaseImage
 * Arguments      	: image - image handle
 * Return         	: none
 * Description    	: load image 
 *					
*/
extern void ez_releaseImage(ezImage_t* image);

/*
 * Function name  	: ez_drawImage
 * Arguments      	: image - image handle
 * Return         	: none
 * Description    	: draw image 
 *					
*/
extern void ez_drawImage(ezImage_t* image, float alpha);

#ifdef __cplusplus
}
#endif 

#endif


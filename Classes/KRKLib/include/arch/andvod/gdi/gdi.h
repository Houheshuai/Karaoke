/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : gdi.h
** Revision : 1.00											
**																	
** Description: ui graphic display low level api
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
*/

#ifndef _GDI_H_
#define _GDI_H_

#define MAX_GDI_FONT_FILE			20

#define CURSOR_BMP_WIDTH	64
#define CURSOR_BMP_HEIGHT	64
#define CURSOR_OSD_WIDTH	24
#define CURSOR_OSD_HEIGHT	24

#define MOVEBMP_WIDTH	40
#define MOVEBMP_HEIGHT	40

#define GDI_CUR_RESO_NUM	1 /* SVGA  */

#define gdi_posx_t GUI_POSX_st

enum
{
	SB_RULE_NONE = 0,
	SB_RULE_SPACE = (1<<1),
	SB_RULE_MIDLINE = (1<<2),
	SB_RULE_EVERYCODE = (1<<3),
	SB_RULE_NK_BOLD = (1<<4),
	SB_RULE_FAKE_MULTI = (1<<5),			// fake multi-stringbitmap
};

enum
{
	ALIGN_LEFT = 0,
	ALIGN_MIDDLE,
	ALIGN_RIGHT,
};

typedef struct
{
	short xmin;
	short xmax;
}gdi_posx_t;

typedef enum
{
	GDI_RESO_QVGA,		/* 320*240 */
	GDI_RESO_VGA,		/* 640*480 */
	GDI_RESO_480p,		/* 720*480 */
	GDI_RESO_576p,		/* 720*576 */
	GDI_RESO_SVGA,		/* 800*600 */
	GDI_RESO_XGA,		/* 1024*768 */
	GDI_RESO_720p,		/* 1280*720 */
	GDI_RESO_SXGA,		/* 1280*1024 */
	GDI_RESO_SXGAPLUS,	/* 1400*1050 */
	GDI_RESO_UVGA,		/* 1600*1200 */
	GDI_RESO_1080p,		/* 1920*1080 */

	GDI_RESO_MAX_CNT,
	
}gdi_resolution_et;

typedef enum
{
	GDI_MAIN_LAYER = 0,
	GDI_CURSOR_LAYER,

	GDI_MAX_LAYERS = 4
} gdi_layer_et;

typedef enum
{
	GDI_COLOR_NONE = 0,
		
	GDI_COLOR_BLACK,
	GDI_COLOR_LIGHTBLACK,
	GDI_COLOR_RED,
	GDI_COLOR_GRAY,
	GDI_COLOR_ORANGE,
	GDI_COLOR_GREEN,
	GDI_COLOR_LIGHTYELLOW,
	GDI_COLOR_BLUE,
	GDI_COLOR_LIGHTGRAY,
	GDI_COLOR_MAGENTA,
	GDI_COLOR_CYAN,
	GDI_COLOR_YELLOW,
	GDI_COLOR_YELLOW2,
	GDI_COLOR_WHITE,
	GDI_COLOR_PINK,
	
} gdi_color_et;

typedef enum
{
	GDI_COLOR_DEEP_1BIT,		/* 2 color */
	GDI_COLOR_DEEP_2BIT,		/* 4 color */
	GDI_COLOR_DEEP_4BIT,		/* 16 color */
	GDI_COLOR_DEEP_8BIT,		/* 256 color */
	GDI_COLOR_DEEP_16BIT,	/* 64K color */
	GDI_COLOR_DEEP_24BIT,	/* true color */
	GDI_COLOR_DEEP_32BIT,	/* true color and gray*/

	GDI_COLOR_DEEP_XBIT_CNT
	
} gdi_color_deep_et;

typedef enum
{
	GDI_FONT_UI = 0,
	GDI_FONT_LYRIC,
	
} gdi_font_et;

typedef enum
{
	FONT_CP_GB2312,
	FONT_CP_UNICODE,
	
}gdi_font_cp_et;

typedef struct 
{

	short width;
	short height;
	
}gdi_size_t;

typedef struct 
{
	short X;				
	short Y;		
	short Width;			
	short Height;			
}gdi_rect_t;

typedef struct 
{
	int x;
	int y;
} ezVector2;

typedef struct 
{
	ezVector2 lt;
	ezVector2 lb;
	ezVector2 rb;
	ezVector2 rt;
	
} Trape4;

typedef struct 
{
	ezVector2 min;
	ezVector2 max;
} Rect2;

enum
{
	ALIGNTYPE_MASK_X = 0x00ff,
	ALIGNTYPE_MASK_Y = 0xff00,
};

typedef enum 
{
	ALIGNTYPE_NONE = 0,
	ALIGNTYPE_LEFT_X,
	ALIGNTYPE_MIDDLE_X,
	ALIGNTYPE_RIGHT_X,
	
	ALIGNTYPE_UP_Y = (1<<8),
	ALIGNTYPE_MIDDLE_Y = (1<<9),
	ALIGNTYPE_DOWN_Y = (1<<10),
	
} gdi_font_align_et;

typedef ezVector2 ezPoint;

typedef struct {
	void* texture;
	void* next;
	int	textureID;
	int	refercount;
	int	layer;
	char* imgFilePath;
	int imgWidth;
	int imgHeight;
	float x;
	float y;
	float width;
	float height;

	void* drawTex[4];					// only use for multi-texture string
		
}gdi_texture_t;

typedef struct 
{
	float x0;
	float y0;
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	
}gdi_utrape_t;

typedef struct 
{
	float xmin;
	float ymin;
	float xmax;
	float ymax;
	
}gdi_urect_t;

typedef struct 
{
	unsigned int		layer;
	gdi_texture_t* cursor_image;
	void* 				cursor_bg;
	int					cursor_width;
	int					cursor_height;
	int					bg_saved;
	int 					bg_x;
	int 					bg_y;
	int					cursor_enable;
} gdi_cursor_t;

typedef struct 
{
	unsigned int		frontColor; 		/* front color */
	unsigned int		frameColor;
	unsigned int		backColor;
	unsigned int 		Size; 		/* Font size */
	unsigned int		leftMargin;
	unsigned int		bottomMargin;
	int						orignalpoint_y;
	int						borderPixel;
	
	gdi_texture_t				strTex;

	unsigned int 				alpha;
	gdi_font_align_et		align;

	int 								notrans;		/* 0: mix alpha with bg, 1: direct copy */
	
	short xBegin;
	short yBegin;
	short bitmapWidth;
	short bitmapHeight;
	
	gdi_font_et hFont;
	
	gdi_posx_t posX[128];
	int posCount;
	int showXBegin;

	int lanType;			// multak font language type, define in multak_font.h

	int wordSpace;

	gdi_utrape_t		strTrape;
	gdi_urect_t 		clipRect;
	float wCutModulusStart;
	float wCutModulusEnd;
		
}gdi_string_t;

typedef struct 
{
	unsigned char *Addr;
	unsigned short RectW; 		/* buffer rect width  */
	
}gdi_DisplayBuf_t;

typedef struct 
{
	gdi_color_deep_et   	ColorDeep;
	unsigned int *      		ColorMap;
	gdi_rect_t          			Screen;
	char*							FrameBuf;
	int								doRender;
	int								used;

} gdi_layer_obj_t;

typedef unsigned int gdi_hdc_t;

struct s_gdi_dc
{	
	unsigned int layer;
	unsigned int locked;
	gdi_hdc_t handle;
	gdi_rect_t *refer_rect;
	gdi_color_et bg_color;
	gdi_color_et fg_color;
	
	struct s_gdi_dc * next;
};

typedef struct s_gdi_dc gdi_dc_t;

typedef enum
{
	GDI_LAYER_NORMAL = 0,
	GDI_LAYER_SPRITE = 1,
	
} gdi_layer_type_t;

typedef enum
{
	GDI_SCREEN_HOST = 0,
	GDI_SCREEN_ASSIST = 1,
	
} gdi_layer_scnno_t;

typedef enum
{
	lyr_TV,
	lyr_VGA,	

}lyc_type_et;

typedef struct 
{
	int		lyr;
	int		width;
	int		height;
	int		logolyr;

	int		lyrtype;	/*TV or VGA*/	
	int		extraheight;		/*����������ʾ�ڴ�*/
} gdi_lyr_st;

typedef struct
{
	unsigned char view;
	unsigned char top;
	unsigned char scrno;
	unsigned char pipe;
	unsigned char type;
}gdi_lyrcreate_st;

typedef struct 
{
	int lantype;
	int fontsize;
	int outlinewidth;
	int borderpixel;
	short startucs;			// start unicode
	short ucslen;					// unicode length
	int	cachebyglyphid;
	
} gdi_font_cache_config_t;

/*
 * font input configuration parameter
*/
typedef struct 
{
	int loadfont;			// 1: load font file, 0: don't load
	int filecount;			// font file count;
	const char* filepath[MAX_GDI_FONT_FILE];
	int fontarea[MAX_GDI_FONT_FILE];

	int fontcache_count;
	gdi_font_cache_config_t* fontcache_conf;
	
} gdi_font_config_t;

/*
 * input configuration of GDI interfaces
*/
typedef struct
{
	gdi_lyr_st 				lyr_para;
	gdi_font_config_t 	font_para;
	
} gdi_configin_t;

#ifdef __cplusplus
extern "C" {
#endif

extern void* gdi_get_default_font(void);

/*
 * Function name  	: gdi_get_cur_resolution
 * Arguments      	: none
 * Return         	: resolution
 * Description    	: get current resolution depend on current system display option
*/
extern gdi_size_t gdi_get_cur_resolution(void);

extern void gdi_load_imgtexture_free(void);

extern gdi_texture_t* gdi_load_imgtexture(const char *path, gdi_texture_t* output);

extern gdi_texture_t* gdi_load_imgtexture_async(const char *path, gdi_texture_t* output);

extern void gdi_load_imgtexture_async_flush(void);

extern gdi_texture_t* gdi_load_strtexture_multi(gdi_string_t* string[], char* str, int count, int rule, int fontNumber);

extern void gdi_release_strtexture_multi(gdi_texture_t* tex0, gdi_texture_t* tex1);

extern int gdi_draw_texture(gdi_texture_t* texture, Trape4* bgTrape, float alpha, void *pImage);

extern void gdi_release_imgtexture(gdi_texture_t* input);
extern void gdi_release_imgtexture_res(gdi_texture_t* input, void *pData);

extern void gdi_release_strtexture(gdi_texture_t* input);

extern void gdi_release_drawtexture(gdi_texture_t* input);

/*
 * Function name  	: gdi_create_texturepalette
 * Arguments      	: layer - create texture in this layer
 *									width - texture pixel width
 *									height - texture pixel height
 * Return         	: texture address
 * Description    	: create a blank image texture
*/
extern gdi_texture_t* gdi_create_texture(int layer, int width, int height);

/*
 * Function name  	: gdi_destroy_texture
 * Arguments      	: tex - input texture address
 * Return         	: texture address
 * Description    	: destroy a  image texture
*/
extern void gdi_destroy_texture(gdi_texture_t* tex);

/*
 * Function name  	: gdi_draw_texture_overlap
 * Arguments      	: tex - input texture address
 * Return         	: texture address
 * Description    	: destroy a  image texture
*/
extern void gdi_draw_texture_overlap(gdi_texture_t* desttex, gdi_texture_t* srctex, int x, int y);

extern void gdi_set_w_cut_modulus(gdi_string_t* str, float wCutModulusStart, float wCutModulusEnd);

/*
 * Function name  	: gdi_draw_rect
 * Arguments      	: dir - 0: from rect to buf, 1: from buf to rect
 *									rect - rect in frame buffer
 *									buf - user data buffer
 *									bufwidth - copy size of width in user buffer
 *									bufheight - copy size of height in user buffer
 *									rectx - x position in rect
 *									recty - y position in rect
 * Return         	: 0 - succ, <> error code
 * Description    	: bitblt between frame buffer rect and user buffer
*/
extern int gdi_rect_bitblt(int dir, gdi_rect_t rect, void* buf, int bufwidth, int bufheight, int rectx, int recty);

/*
 * Function name  	: gdi_clear_full_screen
 *
 * Return         	: none
 * Description    	: Clear full screen to transparent 
*/
extern void gdi_clear_full_screen(int layer);

/*
 * Function name  	: gdi_clear_rect
 *
 * Return         	: none
 * Description    	: Clear a rect
*/
extern void gdi_clear_rect(unsigned int layer, gdi_rect_t area);

extern void gdi_set_string_area(gdi_string_t* str, gdi_rect_t *area);

extern gdi_texture_t* gdi_load_strtexture(gdi_string_t* string, char* str, int rule, int fontNumber);

extern void gdi_string_space_align(gdi_string_t* str1, gdi_string_t* str2, int alignType);

extern void gdi_string_adjust(gdi_string_t* str, char* adjarray, int count);

/*
 * Function name  	: gdi_text_out
 * Arguments      	: hdc - hdc id
 * 			      			: string - gdi string handle
 * Return         	: none
 * Description    	: draw a text string by font config
*/
extern int gdi_text_out(gdi_hdc_t hdc, gdi_string_t *string);
extern int gdi_text_out_ext(gdi_hdc_t hdc, gdi_string_t *str);

/*
 * Function name  	: gdi_text_out2buff
 * Arguments      	: hdc - hdc id
 * 			      		Text - text string pointer
 *					Font - Font config
 * Return         	: none
 * Description    	: draw a text string by font config to Buff
*/
extern int gdi_text_out2buff(gdi_hdc_t hdc, gdi_string_t *string, gdi_DisplayBuf_t *BuffInfo);

extern void gdi_set_cursor_image(gdi_texture_t* texture);

/*
 * Function name  	: gdi_cursor_enable
 * Arguments      	: none
 *                           
 * Return         	: none
 * Description    	: enable cursor draw
*/
extern void gdi_cursor_enable(void);
/*
 * Function name  	: gdi_cursor_disable
 * Arguments      	: none
 *                           
 * Return         	: none
 * Description    	: disable cursor draw
*/
extern void gdi_cursor_disable(void);

extern void gdi_set_layer_visible(unsigned int layer, int setting);

extern void gdi_set_layer_top(unsigned int layer);

extern void gdi_get_layer_rect(unsigned int layer, gdi_rect_t *rect);

extern unsigned int gdi_set_layer_rect(unsigned int layer, gdi_rect_t lyr_rect);

extern void gdi_sel_layer(unsigned int layer);

/*
 * Function name  	: gdi_set_layer
 * Arguments      	: layer - layer handler, rect - layer position and size
 * Return         	: 0 - succ, <>0 error code
 * Description    	: set layer new position and size
*/
extern unsigned int gdi_set_layer(unsigned int layer, gdi_rect_t lyr_rect, gdi_rect_t mask);

/*
 * Function name  	: gdi_create_layer
 * Arguments      	: name - layer name string, rect - layer position and size, para - create para
 * Return         	: layer object handler
 * Description    	: create a graphic layer
*/
extern unsigned int gdi_create_layer(const char* name, gdi_rect_t rect, void * para);

/*
 * Function name  	: gdi_destroy_layer
 * Arguments      	: layer object handler
 *				: scrno screen number
 * Return         	: 0 - succ, <>0 error code
 * Description    	: destroy a graphic layer
*/
extern unsigned int gdi_destroy_layer(unsigned int layer,int scrno);

/*
 * Function name  	: gdi_render_begin
 * Arguments      	: para - input parameter
 * Return         	: none
 * Description    	: do something prepareing for render
*/
extern void gdi_render_begin(void* para);

/*
 * Function name  	: gdi_render_end
 * Arguments      	: para - input parameter
 * Return         	: none
 * Description    	: do something after finished render
*/
extern void gdi_render_end(void* para);

/*
 * Function name  	: krk_gdi_init
 * Arguments      	: 
 *                    option - 1: load font, 0 - not load font
 * Return         	: none
 * Description    	: initialize graphic display layer
*/
extern int krk_gdi_init(void * option);

/*
 * Function name  	: krk_gdi_deinit
 * Arguments      	: 
 *                    option - 1: load font, 0 - not load font
 * Return         	: none
 * Description    	: recover gdi setup to original option
*/
extern void krk_gdi_deinit(void * option);

#ifdef __cplusplus
}
#endif

#endif


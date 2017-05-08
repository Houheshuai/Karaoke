#ifndef _CLABEL_H_
#define _CLABEL_H_

/* TODO: INCLUDE FATHER WIDGET */
#include <gui/widgets/CWidget.h>
/* TODO END */

#define CLabel_ClassID						3

/* TODO: REGISTER METHODS&EVENTS */
#define CLabel_RegMethods(label) {\
	ezRegMethod(Widget(label), CLabel, constructor);\
	ezRegMethod(Widget(label), CLabel, destructor);\
	ezRegMethod(Widget(label), CLabel, drawSelf);\
	ezRegMethod(Widget(label), CLabel, updateSelf);\
	ezRegMethod(Widget(label), CLabel, setIntValue);\
	ezRegMethod(Widget(label), CLabel, setStrValue);\
	ezRegMethod(Widget(label), CLabel, setValue);\
	ezRegMethod(Widget(label), CLabel, setLayer);\
	ezRegMethod(Widget(label), CLabel, transform);\
	ezRegMethod(label, CLabel, setCaption);\
	ezRegMethod(label, CLabel, setImageID);\
	ezRegMethod(label, CLabel, setStringID);\
	ezRegMethod(label, CLabel, playAnimate);\
	ezRegMethod(label, CLabel, stopAnimate);\
}
/* TODO END */

typedef struct s_CLabel CLabel_t;

/* TODO: LABEL RESOURCE */
enum {
	LabelRes_Type_ID = 0,				/* 0 - string label, >0 - image count */
	LabelRes_StartImage_ID,			/* start image resource id */
	LabelRes_ShowStrLen_ID,		/* label限制显示字符串长度 */
	LabelRes_ImageAlign_ID,		/* image align type, see 'CLabelImageAlignX_et', 'CLabelImageAlignY_et' */
	LabelRes_AppendDot_ID,		/* append ... to the end of string if  LabelRes_ShowStrLenID is not 0 */
	LabelRes_AnimateTime_ID,		/* display images in this time, micro second */
	LabelRes_CacheImages_ID,		/* load images in constructor */
	LabelRes_StartString_ID, 		/* start string resource id */
	LabelRes_StringCount_ID,		/* count of string in resource */
	LabelRes_BgColor_ID,				/* background color, if this color is not zero, direct copy string to bg, no alpha blend, faster speed */
	LabelRes_Count,
};
/* TODO END */

/* TODO: LABEL EVENT ID */
enum LabelEventID {
	LabelEvent_onChanged = ((CLabel_ClassID<<8) + 1),

	LabelEventCount
};
/* TODO END */

/* TODO: LABEL EVENT ARGUMENT */
typedef struct {
	WidgetEventArgs_t		we;

} LabelEventArgs_t;
/* TODO END */

/* TODO: METHOD FUNCTION TYPE */
typedef int (*LabelSetCaption_t)(CLabel_t*, char*);
typedef int (*LabelSetImageID_t)(CLabel_t*, int);
typedef int (*LabelSetStringID_t)(CLabel_t*, int);
typedef int (*LabelPlayAnimate_t)(CLabel_t*);
typedef int (*LabelStopAnimate_t)(CLabel_t*);
/* TODO END */

/* label type */
typedef enum {

	CLabelType_String = 0,
	CLabelType_Image,
	
} CLabelType_et;

/* label image align */
typedef enum {

	CLabelImageAlign_xLeft = 1,
	CLabelImageAlign_xMiddle = 2,
	CLabelImageAlign_xRight = 4,
	CLabelImageAlign_yTop = 8,
	CLabelImageAlign_yMiddle = 16,
	CLabelImageAlign_yBottom = 32,
	
} CLabelImageAlign_et;

struct s_CLabel
{

	CWidget_t 						Widget;

	/* TODO: ATTRIBUTES  */
	ezString_t						caption;
	CLabelType_et				labelType;
	int									imageStartID;
	int									imageCount;
	int									showStrLen;
	CLabelImageAlign_et		imageAlign;
	int									appendDot;
	ezImage_t**							images;
	int									stringStartID;
	int									stringCount;
	unsigned int					bgColor;

	/* animate parameters */
	int									animateCircleTime;
	int									animateCurTime;
	int									animateCurFrame;
	int									animateState;
	
	/* TODO END */
	
	/* TODO: METHODS  */
	LabelSetCaption_t			setCaption;
	LabelSetImageID_t			setImageID;
	LabelSetStringID_t			setStringID;
	LabelPlayAnimate_t		playAnimate;
	LabelStopAnimate_t		stopAnimate;
	/* TODO END */
	
	/* TODO: EVENTS */
	/* TODO END */
	
} ;

#ifdef __cplusplus
extern "C" {
#endif 

/* TODO: MSG PROC DECLARATION */
EZGUI_MSGPROC_DECLARE(CLabel);
/* TODO END */

#ifdef __cplusplus
}
#endif 

#endif


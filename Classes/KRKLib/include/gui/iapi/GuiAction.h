/*
** make a GUI application easy and clear							
**
** Filename : GuiAction.h
**																	
** Description: implement gui window action
** 
**************************************************************
** History:
**
** v1.00 : first release
**
**************************************************************
** 
** HOW TO 
**
** sample of startAction
**
**		ezAction_t action; 
**		action.type = ezActionType_Move+ezActionAlpha_NoFade+ezAction_Linear;
**		action.dir = ezActionDir_Forward;
**		action.actPath = {100,100};
**		action.owner = widget;
**		action.fps = 30;
**		action.frames = 15;
**		action.loop = false;
**		ez_startAction(&action);
**
** call ez_updateAction(&action, timeElapsed); in widget_updateSelf(timeElapsed);
*/

#ifndef _GUI_ACTION_H_
#define _GUI_ACTION_H_

/*
*	action type
*/
typedef enum
{
	ezActionType_None = 0,
	ezActionType_Move = (1<<0),					/* normally move action */
	ezActionType_MaskMove = (1<<1),			/* normally move, but region not in mask rect will be hidden */
	ezActionType_Zoom = (1<<2),			/* normally move, but region not in mask rect will be hidden */
	
} ezActionType_et;

/*
*	action alpha type
*/
typedef enum
{
	ezActionAlpha_NoFade = (0<<8),
	ezActionAlpha_FadeIn = (1<<8),
	ezActionAlpha_FadeOut = (2<<8),
	
} ezActionAlphaFade_et;

/*
*	action linear type
*/
typedef enum
{
	ezAction_Linear = (1<<16),
	ezAction_Nonlinear = (2<<16),
	
} ezActionLinearType_et;

/*
*	action state
*/
typedef enum
{
	ezActionState_Idle = 0,
	ezActionState_Stop,
	ezActionState_End,
	ezActionState_Pause,
	ezActionState_Ready,
	ezActionState_Running,
	
} ezActionState_et;

/*
*	action direction
*/
typedef enum
{
	ezActionDir_Forward = 0,
	ezActionDir_Backward,
	
} ezActionDir_et;

/*
* action running parameters
*/
typedef struct 
{
	int										type;				/* action type, see ezActionType_et */
	ezActionDir_et						dir;					/* forward: move from original position to destiny position , backward: reversed */
	ezVector2								actPath;			/* move path, x, y are delta width and delta height to move */
	gdi_rect_t							actRect;			/* rect parameter, in mask move action,it's mask rect, in zoom action, it's zoom rect */
	void*									owner;			/* the window which own this action */
	int										fps;					/* frames per seconds */
	int										frames;			/* total frames of this action */
	int										extframes;	/* use in nonlinear mode */
	int										startFrame;	/* action run from this frame id */
	int										loop;				/* action will restart after ended */
} ezActionPara_t;

/*
* action handler structure
*/
typedef struct 
{
	ezActionPara_t					para;				/* action setting parameters */
	ezActionState_et					state;				/* action running state */
	unsigned int							timeElapsed;/* time elapsed in ms after action started */
	//unsigned int							curTime;
	ezVector2								startPos;		/* move start position, x, y are widget start moving position */
	int										curFrame;		/* current frame index */
	
} ezAction_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  		: ez_startAction
 * Arguments      		: action - input action handle
 * Return         			: 0: succ, <>0: error code
 * Description    			: start action 
 *					
*/
extern int ez_startAction(ezAction_t* action);

/*
 * Function name  		: ez_pauseAction
 * Arguments      		: action - input action handle
 * Return         			: 0: succ, <>0: error code
 * Description    			: pause action 
 *					
*/
extern int ez_pauseAction(ezAction_t* action);

/*
 * Function name  		: ez_stopAction
 * Arguments      		: action - input action handle
 * Return         			: 0: succ, <>0: error code
 * Description    			: stop action, owner go to the original position
 *					
*/
extern int ez_stopAction(ezAction_t* action);

/*
 * Function name  		: ez_endAction
 * Arguments      		: action - input action handle
 * Return         			: 0: succ, <>0: error code
 * Description    			: end action, owner go to the destiny position
 *					
*/
extern int ez_endAction(ezAction_t* action);

/*
 * Function name  		: ez_updateAction
 * Arguments      		: action - input action handle
 *										timeElapsed - time elapsed in ms
 * Return         			: 0: succ, <>0: error code
 * Description    			: update action frame
 *					
*/
extern int ez_updateAction(ezAction_t* action, unsigned int timeElapsed);

#ifdef __cplusplus
}
#endif

#endif

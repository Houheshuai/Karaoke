#ifndef _CHAOS_CDG_H_
#define _CHAOS_CDG_H_



typedef void *ChaosCDGHandle;



ChaosCDGHandle ChaosCDG_Init (char *Path);
void ChaosCDG_Deinit (ChaosCDGHandle Handle);



#define CHAOS_CDG_FULL_WIDTH			300
#define CHAOS_CDG_FULL_HEIGHT			216
#define CHAOS_CDG_FULL_SIZE			(CHAOS_CDG_FULL_WIDTH * CHAOS_CDG_FULL_HEIGHT)
#define CHAOS_CDG_COLOR_BITS			16

typedef struct tagCHAOS_CDG_DATA
{
	unsigned char Data[CHAOS_CDG_FULL_SIZE];
	unsigned long Palette[CHAOS_CDG_COLOR_BITS];
}CHAOS_CDG_DATA;

int ChaosCDG_GetData (ChaosCDGHandle Handle, unsigned long Time, CHAOS_CDG_DATA *Data);



#endif

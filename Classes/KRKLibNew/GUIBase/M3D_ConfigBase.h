#ifndef _M3D_CONFIG_BASE_H
#define _M3D_CONFIG_BASE_H

#ifdef _WIN32
#include <windows.h>
#else
#include <math.h>
#endif

enum{
	M3D_SMALL_ENDIAN = 0,
	M3D_BIG_ENDIAN,
};

// core version
#define M3D_CORE_VERSION	"v1.00"
#define M3D_RES_VERSION		1000

#define M3D_CHANGEVALUE(NUM,MAX)	(NUM = ((NUM+1)>(MAX)? 0:(NUM+1)))

// endian
//#define M3D_ARCH_ENDIAN		M3D_SMALL_ENDIAN

// debug 
#ifdef _WIN32
extern void DebugMsg2(char* szMessage, ...);
#define M3D_DebugPrint DebugMsg2
//#else
//#define M3D_DebugPrint(...)
//#endif
#else
//#include "OGLUtil.h"
#ifdef RELEASE_VERSION

#define M3D_DebugPrint(...)
#else

#include <android/log.h>
//#undef  M3D_DebugPrint
#define M3D_DebugPrint(...) __android_log_print(ANDROID_LOG_INFO, "ms68C", __VA_ARGS__)
#endif

#endif

// sleep
#ifdef _WIN32
#define M3D_Sleep(sec)		Sleep(sec)
extern float GetOSTime();
#else
#include <unistd.h>
#define M3D_Sleep(sec)		usleep(sec)

#include <sys/time.h>
extern unsigned long GetTickCount();
#endif

// file op
#define M3D_FILE			FILE*
#define M3D_ERR_FILE		NULL
#define M3D_OM_RD			"rb"
#define M3D_OM_RW			"rb+"
#define M3D_OM_CREAT		"wb+"
#define M3D_fopen(fn, mode)			fopen(fn, mode)
#define M3D_fclose(fp)				fclose(fp)
#define M3D_fread(buf, size, fp)	fread(buf,1,size,fp)
#define M3D_fwrite(buf, size, fp)	fwrite(buf,1,size,fp)
#define M3D_fseek(fp, off, from)	fseek(fp, off, from)
#define M3D_feof(fp)				feof(fp)
#define M3D_fgets(str, len, fp)		fgets(str, len, fp)
#define M3D_fputs(str, fp)			fputs(str, fp)
#ifdef WIN32
#define M3D_fremove(fname)		remove(fname)
#define M3D_fabs(a)				abs(a)
#else
#define M3D_fremove(fname)		unlink(fname)
#define M3D_fabs(a)				fabs(a)
#endif

#define M3D_WIN_ID_NONE			0
#define M3D_CLASS_ID_NONE		0

#define M3D_UI_KEY_A            0X41
#define M3D_UI_KEY_B            0X42
#define M3D_UI_KEY_C            0X43
#define M3D_UI_KEY_D            0X44
#define M3D_UI_KEY_E            0X45
#define M3D_UI_KEY_F            0X46
#define M3D_UI_KEY_G            0X47
#define M3D_UI_KEY_H            0X48
#define M3D_UI_KEY_I            0X49
#define M3D_UI_KEY_J            0X4A
#define M3D_UI_KEY_K            0X4B
#define M3D_UI_KEY_L            0X4C
#define M3D_UI_KEY_M            0X4D
#define M3D_UI_KEY_N            0X4E
#define M3D_UI_KEY_O            0X4F
#define M3D_UI_KEY_P		    0X50
#define M3D_UI_KEY_Q            0X51
#define M3D_UI_KEY_R            0X52
#define M3D_UI_KEY_S            0X53
#define M3D_UI_KEY_T            0X54
#define M3D_UI_KEY_U            0X55
#define M3D_UI_KEY_V            0X56
#define M3D_UI_KEY_W            0X57
#define M3D_UI_KEY_X            0X58
#define M3D_UI_KEY_Y            0X59
#define M3D_UI_KEY_Z            0X5A

#ifdef _WIN32
// keys value define
#define M3D_UI_KEY_UP			VK_UP
#define M3D_UI_KEY_DOWN			VK_DOWN
#define M3D_UI_KEY_LEFT			VK_LEFT
#define M3D_UI_KEY_RIGHT		VK_RIGHT
#define M3D_UI_KEY_ENTER		VK_RETURN		


#else
/*
typedef enum {
	mKey_Null,		
	mKey_Up,
	mKey_Down,
	mKey_Left,
	mKey_Right,
	mKey_Enter,		

	mKey_BaseTotal
} ShortKey_m ;
		
#define M3D_UI_KEY_UP			mKey_Up
#define M3D_UI_KEY_DOWN			mKey_Down
#define M3D_UI_KEY_LEFT			mKey_Left
#define M3D_UI_KEY_RIGHT		mKey_Right
#define M3D_UI_KEY_ENTER		mKey_Enter
		*/
#endif

#define M3D_UI_KEY_FAST_UP              60
#define M3D_UI_KEY_FAST_DOWN			61
#define M3D_UI_KEY_FAST_LEFT			62
#define M3D_UI_KEY_FAST_RIGHT			63
   
#define M3D_UI_JOYSTICK_KEY_1           112          // Key Order, F1 on PC
#define M3D_UI_JOYSTICK_KEY_2           113          // Key NewPK, F2 on PC
#define M3D_UI_JOYSTICK_KEY_A           114          // Key Yes, F3 on PC
#define M3D_UI_JOYSTICK_KEY_B           115          // Key Confirm, F4 on PC
#define M3D_UI_JOYSTICK_KEY_M           116          // Key Menu, F5 on PC

#endif

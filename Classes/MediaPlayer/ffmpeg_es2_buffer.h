#ifndef VIDEO_OPENGLES2_HH
#define VIDEO_OPENGLES2_HH

#define MAX_ES2_FRAME 2

typedef struct _gles2_frame_t
{
	int					index;
	unsigned int		w;
	unsigned int		h;
	unsigned int		linesize;
	unsigned int		datalen;
	unsigned char		*videobuf;
	int					nHardWareDecode;
} gles2_frame_t;


extern gles2_frame_t gles2_pVideoFrame[MAX_ES2_FRAME];
extern int gles2_WritePos;
extern int g_displayVideo;

#endif

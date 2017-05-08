#ifndef VIDEO_OPENGLES2
#define VIDEO_OPENGLES2

#include "renderers/renderer.h"

#undef PLAYER_VIDEO_GLES2

#ifdef __cplusplus
extern "C" {
#endif 

extern void	*mpr_video_gles2_new      (void *data);
extern void	mpr_video_gles2_free      (void *data);
extern unsigned char	mpr_video_gles2_open      (void *data, unsigned int width, unsigned int height, unsigned int actual_width, unsigned int actual_height,  unsigned int pix_fmt, int vformat);
extern void	mpr_video_gles2_close     (void *data);
extern unsigned char	mpr_video_gles2_queue_new (void *data, void *pFrame, void **storage);
extern void	mpr_video_gles2_queue_free(void *data, void *pFrame, void **storage);
extern unsigned char	mpr_video_gles2_queue     (void *data, void *pFrame, void **storage);
extern unsigned char	mpr_video_gles2_display   (void *data, void **storage);
extern void	mpr_video_gles2_drop      (void *data, void **storage);


DEFINE_VIDEO_RENDERER(PLAYER_VIDEO_GLES2,
	mpr_video_gles2_new,
	mpr_video_gles2_free,
	mpr_video_gles2_open,
	mpr_video_gles2_close,
	mpr_video_gles2_queue_new,
	mpr_video_gles2_queue_free,
	mpr_video_gles2_queue,
	mpr_video_gles2_display,
	mpr_video_gles2_drop,
	1
);

#ifdef __cplusplus
}
#endif 

#endif

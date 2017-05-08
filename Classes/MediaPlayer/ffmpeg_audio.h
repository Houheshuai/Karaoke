#ifndef AUDIO_CHAOS
#define AUDIO_CHAOS

#include "renderers/renderer.h"

#undef PLAYER_AUDIO_CHAOS

#ifdef __cplusplus
extern "C" {
#endif 

extern void	*mpr_audio_chaos_new(void *data);
extern void	mpr_audio_chaos_free    (void *data);
extern unsigned char	mpr_audio_chaos_open    (void *data, unsigned int rate, unsigned int channels, int index);
extern void	mpr_audio_chaos_close   (void *data);
extern double	mpr_audio_chaos_getdelay(void *data);
extern unsigned char	mpr_audio_chaos_write   (void *data, int16_t *samples, unsigned int frames);
extern void	mpr_audio_chaos_pause   (void *data);
extern void	mpr_audio_chaos_resume  (void *data);
extern void	mpr_audio_chaos_seek  (void *data);


DEFINE_AUDIO_RENDERER(PLAYER_AUDIO_CHAOS,
	mpr_audio_chaos_new,
	mpr_audio_chaos_free,
	mpr_audio_chaos_open,
	mpr_audio_chaos_close,
	mpr_audio_chaos_getdelay,
	mpr_audio_chaos_write,
	mpr_audio_chaos_pause,
	mpr_audio_chaos_resume,
	mpr_audio_chaos_seek
);

#ifdef __cplusplus
}
#endif

#endif

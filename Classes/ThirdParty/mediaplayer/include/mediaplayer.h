#ifndef _H_PLAYER_
#define _H_PLAYER_

#include "renderers/renderer.h"

/*
#include "renderers/audio/alsa.h"
#include "renderers/video/xv.h"
#include "renderers/video/directfb.h"
#include "renderers/video/gtk.h"
*/


typedef struct mp mp_t;
typedef unsigned char (*mp_func_event)(void *data);

enum mp_event_type {
	MP_EVENT_PTS_VALUE		,
	MP_EVENT_MASTER_CLOCK_TICK	,
	MP_EVENT_AUDIO_SYNC
};

/* create a new player */
mp_t*	mp_new();

/* free the supplied player */
void		mp_free(mp_t *p);

/* load the supplied file */
unsigned char		mp_load(mp_t *p, char* filename);

/* returns the number of streams for the specified codec type (CODEC_TYPE_AUDIO/CODEC_TYPE_VIDEO etc) */
unsigned int	mp_num_streams(mp_t *p, unsigned int type, char *strCodec, int len);

/* setup the specified stream's renderer (data is user data to pass to the renderer, eg, context to draw on) */
unsigned char		mp_setup_stream(mp_t *p, unsigned int index, mp_renderer_t *renderer, void* data);

/* open the streams/codecs */
unsigned char		mp_open(mp_t *p);

/* close the streams, and file */
void		mp_close(mp_t *p);

void		mp_play(mp_t *p);
unsigned char		mp_is_playing(mp_t *p);
unsigned char		mp_is_paused(mp_t *p);

void		mp_pause(mp_t *p);
void		mp_stop(mp_t *p);
void		mp_seek(mp_t *p, double pts);

/* block until playback to completes */
void		mp_wait(mp_t *p);

//hh:mm:ss.fr
void		mp_gettotaltime(mp_t *p, int *hour, int *min, int *sec, int *fr, int *totalUs);

/* add an event of the specified type to call back */
void		mp_add_event(mp_t *p, enum mp_event_type type, double pts, mp_func_event fn_event, void* data);

void mp_set_sdkversion(int version) ;

#endif

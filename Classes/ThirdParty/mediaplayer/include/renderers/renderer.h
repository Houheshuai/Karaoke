/***************************************************************************
 *   Copyright (C) 2009 by Geoffrey McRae   *
 *   geoff@spacevs.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _H_RENDERER_
#define _H_RENDERER_
//#include <stdint.h>

#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)

#ifdef WIN32
#define __attribute__(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif 
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif 

#define PLAYER_RENDERER_AUDIO	AVMEDIA_TYPE_AUDIO
#define PLAYER_RENDERER_VIDEO	AVMEDIA_TYPE_VIDEO

typedef struct mp_renderer mp_renderer_t;
struct mp_renderer {
	unsigned int	iType;
	char		*cName;

	void *(*newData )(void *data);	/* this function may return a pointer to data that is passed to all future renderer calls */
	void  (*freeData)(void *data);

	/* audio functions */
	unsigned char  (*audio_open      )(void *data, unsigned int rate, unsigned int channels, int index);
	void  (*audio_close     )(void *data);
	double(*audio_getdelay  )(void *data);
	unsigned char  (*audio_write     )(void *data, int16_t *samples, unsigned int frames);
	void  (*audio_pause     )(void *data);
	void  (*audio_resume    )(void *data);
	void  (*audio_seek    )(void *data);

	/* video functions */
	unsigned char  (*video_open      )(void *data, unsigned int width, unsigned int height, unsigned int actual_width, unsigned int actual_height, unsigned int pix_fmt, int vformat);
	void  (*video_close     )(void *data);
	unsigned char  (*video_queue_new )(void *data, void *pFrame, void **storage);
	void  (*video_queue_free)(void *data, void *pFrame, void **storage);
	unsigned char  (*video_queue     )(void *data, void *pFrame, void **storage);
	unsigned char  (*video_display   )(void *data, void **storage);
	void  (*video_drop      )(void *data, void **storage);

	/* this specifies how many frames the renderer wants to queue up before commencing playback */
	unsigned int video_queue_size;
};

#define DEFINE_AUDIO_RENDERER(name, newData, freeData, open, close, getdelay, write, pause, resume, seek)			\
static mp_renderer_t _ ##name = {										\
	PLAYER_RENDERER_AUDIO,											\
	#name,													\
	newData,													\
	freeData,													\
	open,													\
	close,													\
	getdelay,												\
	write,													\
	pause,													\
	resume,													\
	seek,													\
	NULL,													\
	NULL,													\
	NULL,													\
	NULL,													\
	NULL,													\
	NULL													\
};														\
static mp_renderer_t* name __attribute__((unused)) = &_ ##name;

#define DEFINE_VIDEO_RENDERER(name, newData, freeData, open, close, queue_new, queue_free, queue, display, drop, queue_size)	\
static mp_renderer_t _ ##name = {											\
	PLAYER_RENDERER_VIDEO,												\
	#name,														\
	newData,														\
	freeData,														\
	NULL,														\
	NULL,														\
	NULL,														\
	NULL,														\
	NULL,														\
	NULL,														\
	NULL,														\
	open,														\
	close,														\
	queue_new,													\
	queue_free,													\
	queue,														\
	display,													\
	drop,														\
	queue_size													\
};															\
static mp_renderer_t* name __attribute__((unused)) = &_ ##name;

#endif

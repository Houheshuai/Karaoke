#ifndef _H_IPLAYER_
#define _H_IPLAYER_

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

#include <pthread.h>
#include <semaphore.h>


#include "mediaplayer.h"

#include "debug.h"
#include "array.h"
#include "ll.h"

#define MAX_VIDEOQ_SIZE 10

//multak
#define OKF_HEAD_SIZE	512


typedef struct mp_stream		mp_stream_t;
typedef struct mp_event			mp_event_t;
typedef struct mp_queue			mp_queue_t;

struct mp {
	AVFormatContext		*pFormatCtx;
	unsigned char			bLoaded;			/* True if there is a file open		*/
	unsigned char			bOpen;				/* True if the streams have been opened	*/
	unsigned int		iNumStreams;			/* The number of streams in the file	*/
	array_t			*aStreams;			/* The streams to process		*/

	pthread_rwlock_t	mRunning;			/* Thread lock for bRunning		*/
	unsigned char			bRunning;			/* True if the demuxer is running	*/

	pthread_t		tDemuxer;			/* The demuxer thread			*/

	unsigned char			bPlaying;			/* True if playback has started		*/
	unsigned char			bPaused;			/* True if the playback is paused	*/
	pthread_t		tClock;				/* The master clock thread		*/
	pthread_mutex_t		mClock;				/* The clock mutex			*/
	pthread_rwlock_t	lClock;				/* The update clock lock		*/
	pthread_cond_t		cClock;				/* The clock condition the streams use	*/
	double			dClock;				/* The clock itself			*/
	unsigned char			bForceClock;			/* True if the clock has been forced	*/

	ll_t			*lEventsPTS;			/* Event that fire on the specified PTS	*/
	ll_t			*lEventsMC;			/* Events that fire on MC update	*/
	ll_t			*lEventsAS;			/* Events that file on Audio Sync	*/

	pthread_rwlock_t	lSeek;				/* The seek lock			*/
	unsigned char			bSeek;				/* True if seeking to pts		*/
	double			dSeek;				/* The pts to seek to			*/

	//okfͨflagļ
	unsigned char	okfFlag;
	FILE			*fHandle;
	int				iBufSize;
	unsigned char   *pBuffer;
	AVIOContext		*pIOCtx;

	pthread_mutex_t		mAudioMutex;
	pthread_mutex_t		mCloseMutex;
};

struct mp_stream {
	mp_t			*p;				/* The player that owns this stream	*/
	unsigned int		iIndex;				/* The stream index			*/
	AVStream		*pStream;			/* The actual stream			*/
	ll_t			*lPackets;			/* The packet queue			*/

	pthread_t		tThread;			/* The thread that handles this stream	*/
	unsigned char			bPrimed;			/* If the thread's buffers are primed	*/

	sem_t			sQueue;				/* The queue size semaphore		*/
	ll_t			*lQueue;			/* Queue items				*/
	unsigned int		iQueueSize;			/* The size of the queue		*/

	mp_renderer_t		*rndr;				/* The stream renderer			*/
	void			*data;				/* The stream renderer's init data	*/
	void			*rndr_data;			/* The stream renderer's data		*/

	unsigned char			bSyncSource;			/* Is the stream is the sync source?	*/
	double			dClock;				/* The streams own clock		*/
	unsigned char			bClockUpdated;			/* Was the clock updated		*/

	pthread_rwlock_t	lStop;				/* bStop lock 				*/
	unsigned char			bStop;				/* Should the stream stop		*/

	pthread_rwlock_t	lRunning;			/* bRunning lock 			*/
	unsigned char			bRunning;			/* Is the stream running		*/

	double				_TimeBase;

};

struct mp_event {
	double			pts;				/* The presintation time to trigger on	*/
	mp_func_event		fn_event;			/* The callback function		*/
	void			*data;				/* Associated data			*/
};

struct mp_queue {
	mp_stream_t		*s;				/* The stream that this item belongs to	*/
	void			*storage;			/* Storage for the video renderer's use	*/
	void		*pFrame;			/* The frame itself			*/
};

/* player.c functions */
mp_stream_t*		mp_stream_new(mp_t *p, mp_renderer_t *renderer);
void			mp_stream_free(void *_data);

/* thread.c functions */
unsigned char		mp_isrunning(mp_t *p);
void		mp_stream_primed(mp_stream_t *s);
void		mp_av_free_packet(void *_data);
void*			mp_thread_demuxer(void *_data);

/* stream.c functions */
void			mp_stream_audio(mp_stream_t *s);
void			mp_stream_video(mp_stream_t *s);
unsigned char			mp_stream_video_update(void* data);

/* time.c functions */
void		mp_add_time(struct timespec *ts, const unsigned long nsec);
void		mp_double_to_ts(const double time, struct timespec *ts);

/* events.c functions */
unsigned char			mp_foreach_event_all(void *data, unsigned char *remove, void *loop_data);
unsigned char			mp_foreach_event_pts(void *data, unsigned char *remove, void *loop_data);


#endif

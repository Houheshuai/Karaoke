#ifndef AUDIO_CHAOS_HH
#define AUDIO_CHAOS_HH

typedef void (*mpr_audio_stop_cb)(void*, int , int);

#ifdef __cplusplus
extern "C" {
#endif 

extern void ffmpeg_audio_mute_set(int muteon);
extern void ffmpeg_audio_volume_set(int volum);
extern void ffmpeg_audio_echo_set(int echo);
extern void ffmpeg_audio_mic1vol_set(int vol);
extern void ffmpeg_audio_mic2vol_set(int vol);
extern void ffmpeg_audio_mic3vol_set(int vol);
extern void ffmpeg_audio_mic4vol_set(int vol);
extern void ffmpeg_audio_default_vocal_set(int vocal);
extern void ffmpeg_audio_vocal_set(int vocal);
extern void ffmpeg_audio_pause(void);
extern void ffmpeg_audio_resume(void);
extern void ffmpeg_audio_vocal_change(void);
extern void ffmpeg_audio_setup(int inrate, int outrate, int inchannels, int outchannels, int latency, int outlatency);
extern void* ffmpeg_audio_init(void* audioIF, void* audioHdle, void* owner, mpr_audio_stop_cb cb);
extern void ffmpeg_audio_deinit(void* playerHdle, void* audioHdle, void* audioIF);
extern void ffmpeg_audio_setRecordPath(char *path);
extern void ffmpeg_audio_recordClose(void);
extern void ffmpeg_audio_semInit(void);
extern void ffmpeg_audio_semDestroy(void);
extern void ffmpeg_audio_vocal_change(void);

#ifdef __cplusplus
}
#endif 

#endif

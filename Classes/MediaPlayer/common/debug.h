#ifndef _H_DEBUG_
#define _H_DEBUG_
#include <stdio.h>

//#define INF(format, args...) fprintf(stderr, "I: " format "\n", args)
//#define ERR(format, args...) fprintf(stderr, "E: " format "\n", args)
//#define WRN(format, args...) fprintf(stderr, "W: " format "\n", args)
#ifndef WIN32
#include <android/log.h>
#define INF(...)	__android_log_print(ANDROID_LOG_INFO,"MEDIA",__VA_ARGS__)
#define ERR(...)	__android_log_print(ANDROID_LOG_INFO,"MEDIA",__VA_ARGS__)
#define WRN(...)	__android_log_print(ANDROID_LOG_INFO,"MEDIA",__VA_ARGS__)
#else
#define INF(...)	printf(__VA_ARGS__)
#define ERR(...)	printf(__VA_ARGS__)
#define WRN(...)	printf(__VA_ARGS__)
#endif
/*
#define INF(...) 
#define ERR(...) 
#define WRN(...) 
*/

#endif

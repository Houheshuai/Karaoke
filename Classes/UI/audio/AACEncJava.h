#ifndef _AAC_ENC_JAVA_H_
#define _AAC_ENC_JAVA_H_

#include <jni.h>

typedef void *AAC_ENC_JAVA_HANDLE;

typedef struct tagAAC_ENC_JAVA_PARAM
{
	JavaVM	*Jvm;
	jclass	Class;
}AAC_ENC_JAVA_PARAM;

#ifdef __cplusplus
extern "C" {
#endif 

int AACEncJava_Open (AAC_ENC_JAVA_HANDLE Handle, unsigned long SampleRate, unsigned long Channels, unsigned long BitRate);
void AACEncJava_Close (AAC_ENC_JAVA_HANDLE Handle);
void AACEncJava_Proc (AAC_ENC_JAVA_HANDLE Handle, void *SrcData, unsigned long *SrcSize, void *DestData, unsigned long *DestSize);

AAC_ENC_JAVA_HANDLE AACEncJava_Init (AAC_ENC_JAVA_PARAM *Param);
void AACEncJava_Deinit (AAC_ENC_JAVA_HANDLE Handle);

#ifdef __cplusplus
}
#endif 

#endif

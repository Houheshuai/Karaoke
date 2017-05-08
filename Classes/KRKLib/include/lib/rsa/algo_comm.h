#ifndef _COMM_H_
#define _COMM_H_

#include <k_define.h>

#ifdef WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

//#define TEST_ALGO

/* Error codes.
 */
#define RE_CONTENT_ENCODING 0x0400
#define RE_DATA 0x0401
#define RE_DIGEST_ALGORITHM 0x0402
#define RE_ENCODING 0x0403
#define RE_KEY 0x0404
#define RE_KEY_ENCODING 0x0405
#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_NEED_RANDOM 0x0408
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_SIGNATURE 0x040b
#define RE_SIGNATURE_ENCODING 0x040c

typedef int (*CMP_CALL_BACK)(void *,void *);
typedef CMP_CALL_BACK  ccb;

typedef unsigned long int UINT4;
typedef UINT4 NN_DIGIT;
typedef unsigned short int UINT2;
typedef UINT2 NN_HALF_DIGIT;

#ifdef __cplusplus
extern "C" {
#endif 

extern void R_memset (void *output,int value,unsigned int len);
extern void R_memcpy (void *output,void *input,unsigned int len);

#ifdef __cplusplus
}
#endif 

#endif


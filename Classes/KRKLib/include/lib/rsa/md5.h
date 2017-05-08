#ifndef _MD5_H_
#define _MD5_H_

typedef struct {
	UINT4 state[4];            /* state (ABCD) */
	UINT4 count[2];            /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];  /* input buffer */
} MD5_CTX;

#ifdef __cplusplus
extern "C" {
#endif

void MD5Init(MD5_CTX *context);
void MD5Update (MD5_CTX *context, 
				unsigned char *input, 
				unsigned int inputLen);
void MD5Final (unsigned char digest[16],MD5_CTX *context);
void MD5(void *output,void *input,unsigned int inputlen);
int MD5_File (char * filename, char Md5Str[33]);

#ifdef __cplusplus
}
#endif

#endif


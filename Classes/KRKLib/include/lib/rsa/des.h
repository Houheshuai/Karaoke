#ifndef _DES_H_
#define _DES_H_

typedef struct {
	unsigned char subkeyBit[16][48];                    
	unsigned char ivBit[64];                
	int encrypt;                                  
} DES_CBC_CTX;

#ifdef __cplusplus
extern "C" {
#endif

void DES_CBC_Final (DES_CBC_CTX *context);
int DES_CBC_Update (DES_CBC_CTX *context,
				   unsigned char * output,
				   unsigned char * input,
				   unsigned int  len);
void DES_CBC_Init (DES_CBC_CTX *context,
				  unsigned char key[8],
				  unsigned char iv[8],
				  int encrypt);
void DES_CEC_Encrypt(unsigned char * Key,
					 unsigned char * iv,
					 char * inbuf,
					 char * outbuf,
					 unsigned int Length);
void DES_CEC_Decrypt(unsigned char * Key,
					 unsigned char * iv,
					 char * inbuf,
					 char * outbuf,
					 unsigned int Length);

#ifdef __cplusplus
}
#endif

#endif


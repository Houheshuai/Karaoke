#ifndef _R_RANDOM_H_
#define _R_RANDOM_H_

#define RANDOM_BYTES_NEEDED 4
/* R_RANDOM.H - header file for R_RANDOM.C
 */


typedef struct {
	unsigned int bytesNeeded;
	unsigned char state[16];
	unsigned int outputAvailable;
	unsigned char output[16];
} R_RANDOM_STRUCT;

#ifdef __cplusplus
extern "C" {
#endif

int R_RandomInit(R_RANDOM_STRUCT *randomStruct);
int R_RandomUpdate(R_RANDOM_STRUCT *randomStruct, unsigned char *block, unsigned int blockLen);
void R_RandomFinal(R_RANDOM_STRUCT *randomStruct);
int R_GenerateBytes (unsigned char *block, unsigned int blockLen, R_RANDOM_STRUCT *randomStruct); 

#ifdef __cplusplus
}
#endif

#endif



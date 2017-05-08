#ifndef _EQ3_H
#define _EQ3_H

#ifdef __cplusplus
extern "C" {
#endif

extern void * CreateEQ(void);
extern int DestroyEQ(void * handle);
extern int SetEQBand(void * handle, int gain, unsigned band);
extern int SetEQSampleRate(void * handle, unsigned SampleRate);
extern int PorcessEQ(void * handle, short *input, short *output, unsigned samplecount);
extern int APF_Porcess_1(void * handle, int input, int *output);
extern int APF_Porcess_2(void * handle, int inputL, int *outputL, int inputR, int *outputR);

#ifdef __cplusplus
}
#endif

#endif


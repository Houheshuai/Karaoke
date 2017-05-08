
#ifndef USERSOUNDALGORITHMGLOBAL_H
#define USERSOUNDALGORITHMGLOBAL_H

//#include "../multak_api.h"


extern const char g_pHummingSearchVersion[16]; 


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#define	UseMemFile
#define	AS_Malloc								malloc
#define	AS_FREE								free

#ifndef UseMemFile
#define	AS_WriteFile(buffer, size1, size2, fd)			fwrite(buffer, size1,size2,fd) 
#define	AS_ReadFile(buffer, size1, size2, fd)			fread(buffer, size1, size2, fd)
#define	AS_OpenReadFile(path)					fopen(path, "rb")
#define	AS_OpenWriteFile(path)					fopen(path, "wb")
#define	AS_CloseReadFile(fd)						fclose(fd)
#define	AS_CloseWriteFile(fd)						fclose(fd)
#define	AS_SeekHead(fd, offset)					fseek(fd, offset, 0)
#define	AS_ReadFileType						FILE*
#define	AS_WriteFileType						FILE*
#else
#define	MAX_VITURE_FILE_NUM	16
typedef struct tagKVirtureFile
{
	char	filename[16];
	char	*data;
	int		offset;
	int		filesize;
}KVirtureFile;

typedef struct tagKVirtureFileTable
{
	KVirtureFile	file[MAX_VITURE_FILE_NUM];
}KVirtureFileTable;

extern KVirtureFileTable	filetable;
extern KVirtureFile* VF_Open(char *filename);
extern int VF_Read(KVirtureFile *file, int size, char *target);
extern int VF_Write(KVirtureFile *file, int size, char *source);
extern int VF_AddReadFile(char *realfilename, char *memfilename);
extern void VF_SeekHead(KVirtureFile *file, int offset);

#define	AS_WriteFile(buffer, size1, size2, fd)		VF_Write(fd, size1*size2, buffer) 
#define	AS_ReadFile(buffer, size1, size2, fd)		VF_Read(fd, size1*size2, buffer)
#define	AS_OpenReadFile(path)					VF_Open(path)
#define	AS_OpenWriteFile(path)					VF_Open(path)
#define	AS_CloseFile(fd)						
#define	AS_SeekHead(fd, offset)					VF_SeekHead(fd, offset)
#define	AS_ReadFileType						KVirtureFileTable*

#endif
#define	AS_PrintError							printf
#define	AS_FileNull							NULL

#define	SYSTEM_ENERGY_THRESHOLD				500		
#define	SAMPLE_RATE 							32000


#define	AS_GetFileSize(fd)		SA_GetFileSize(fd)

extern int	SA_TransferInputData(short *StartInputL, short *StartInputR, int MonoSampleLen, int SampleStep, int *Output);



extern int	SA_TransferOutputData(int *Input, int MonoSampleLen, int SampleStep, short *StartOutputL, short *StartOutputR);


extern int	SA_InitPool(char *pool, int poolsize);



extern char* SA_MallocFromPool(int mallocsize, char *pool, int poolsize);


extern int SA_FreeFromPool(char *pt, char *pool, int poolsize);

#endif

#ifndef DB_CONFIGURE
#define DB_CONFIGURE

#include <k_global.h>

#define DB_MODULE_SQL	1		/* SQL rountines support */

#if (defined _KRK_DEBUG_) || (defined _KRK_ROM_DEBUG_)
#define DB_DEBUG 		1		/* debug switch */
#else
#define DB_DEBUG 		0		/* debug switch */
#endif

#define SQL_READ_BUFFER_SIZE		(64*1024)	/* SQL read buffer size */

#define DB_KERNEL_SMALL_ENDIAN		KRK_SMALL_ENDIAN
#define DB_KERNEL_BIG_ENDIAN		KRK_BIG_ENDIAN

#define _db_inline	KRK_INLINE

/* fs config */
#define DB_FILE	FILE*

#define DB_OM_RDONLY 		"rb"
#define DB_OM_WRONLY 		"wb"
#define DB_OM_RDWR			"rb+"
#define DB_FOPEN_ERR		NULL
#define DB_FOLDER_SYMBOL	KRK_PATH_SPLIT
#define DB_OM_CREATE		"wb+"

/* file opr for edb file */
#define _fopr_fopen(a,b) fopen((const char *)a,b)
#define _fopr_fwrite(a,b,c,d) fwrite(a,b,c,d)
#define _fopr_fread(a,b,c,d) fread(a,b,c,d)
#define _fopr_freadfail(a, b, c, d) (fread(a, b, c, d) != c)
#define _fopr_fwritefail(a, b, c, d) (fwrite(a, b, c, d) != c)
#define _fopr_freadsucc(a, b, c, d) (fread(a, b, c, d) == c)
#define _fopr_fwritesucc(a, b, c, d) (fwrite(a, b, c, d) == c)
#define _fopr_fsize(a) krk_fsize(a)
#define _fopr_fclose(a) fclose(a)
#define _fopr_fseek(a,b,c) fseek(a,b,c)
#define _fopr_ftell(a) ftell(a)
#define _fopr_fremove(a)  remove((const char *)a)
#define _fopr_fremovesucc(a) (remove((const char *)a)==0)

/* file opr for other files */
#define _db_fopen(a,b)		fopen((const char *)a,b)
#define _db_fwrite(a,b,c,d)	fwrite(a,b,c,d)
#define _db_fread(a,b,c,d)	fread(a,b,c,d)
#define _db_freadfail(a, b, c, d) (fread(a,b,c,d) != c)
#define _db_fwritefail(a, b, c, d) (fwrite(a,b,c,d) != c)
#define _db_freadsucc(a, b, c, d) (fread(a,b,c,d) == c)
#define _db_fwritesucc(a, b, c, d) (fwrite(a,b,c,d) == c)
#define _db_freadline(a, b, c) __freadline(a, b, c)
#define _db_fsize(a)			krk_fsize(a)
#define _db_fseek(a,b,c)		fseek(a,b,c)
#define _db_fclose(a)			fclose(a)
#define _db_ftell(a) ftell(a)
#define _db_removefile(a)	remove((const char *)a)

#define _db_malloc(a)		malloc(a)
#define _db_free(a)			free(a)

#define _db_strlen(a)			strlen((const char *)a)		/*字符串结尾的0 不计算在内*/
#define _db_strcpy(a,b)		strcpy((char *)a,(const char *)b)
#define _db_strncpy(a,b,c)	strncpy((char *)a,(const char *)b,c)
#define _db_memmove(a,b,c)	memmove(a,b,c)
#define _db_memcpy(a,b,c)	memcpy(a,b,c)
#define _db_memset(a,b,c)	memset(a,b,c)
#define _db_strncmp(a,b,c)	strncmp((const char *)a,(const char *)b,c)
#define _db_strcat(a,b)		strcat((char *)a,(const char *)b)
#define _db_strcmp(a,b)	strcmp((const char *)a,(const char *)b)
#define _db_stricmp(a,b)	stricmp((const char *)a,(const char *)b)
#define _db_sprintf			sprintf
#define _db_print(...)		 KRK_PRINTF(__VA_ARGS__)
#define _db_exchange(p, q)	 do { \
								 unsigned char tmp_xxxx;\
								 tmp_xxxx = *p;\
								 *p = *q;\
								 *q = tmp_xxxx;\
							} while (0);

#define _db_lock()
#define _db_unlock()

#define _db_assert(a)	KRK_ASSERT(a)

#ifndef FILE_EXIST
#define FILE_EXIST(a)			((a) != NULL)
#endif

#if (DB_SINGLE_FILE == 0)
/* file opr for edb file */
#define DB_FILE_P DB_FILE
#define DB_FILE_OPEN_FAIL  DB_FOPEN_ERR

#define db_fcreate(a) 		_fopr_fopen(a,DB_OM_CREATE)
#define db_fopen(a, b) 		(DB_FILE_P)_fopr_fopen(a,(b == DB_READ_ONLY)?DB_OM_RDONLY : DB_OM_CREATE)
#define db_fwrite(a,b,c,d)	_fopr_fwritefail(a,b,c,d)
#define db_fread(a,b,c,d) 	_fopr_freadfail(a,b,c,d)
#define db_fsize(a) 		_fopr_fsize(a)
#define db_fclose(a) 		_fopr_fclose(a)
#define db_fseek(a,b,c) 	_fopr_fseek(a,b,c)
#define db_ftell(a) 		_fopr_ftell(a)
#define db_table_fopen(a, b, c) (DB_FILE_P)_fopr_fopen(b,(c)? DB_OM_CREATE : DB_OM_RDONLY)
#define db_table_fclose(a) 		_fopr_fclose(a)
#define db_table_fremove(a,b) 	_fopr_fremove(b)
#define db_table_fremove_succ(a,b) 	_fopr_fremovesucc(b)
#else
#define DB_FILE_OPEN_FAIL  NULL
#define db_table_fremove_succ(a,b) 	db_table_fremove(a,b)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

extern DB_INT32 __freadline(DB_FILE fp, t_FILE_LINE *fline, int max_len);
extern DB_UINT32 GetNbytesLSB(DB_UINT32 nNumber, DB_UINT8 *address);
extern DB_UINT32 GetNbytesMSB(DB_UINT32 nNumber, DB_UINT8 *address);

#ifdef __cplusplus
}
#endif 

#endif

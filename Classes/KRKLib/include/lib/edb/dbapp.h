#ifndef _DBAPP_H_
#define _DBAPP_H_

/* customorize you own applications on the following */

#if DB_MODULE_SQL > 0
#define DB_APP_SQL_FILE			1		/* include SQL file supported */
#endif

#define DB_APP_OKF_FILE		0		/* update OKF file application */

#define DB_APP_MERGE_DB		0		/* merge db files */

#if DB_APP_MERGE_DB > 0

#define DB_MERGE_LEVEL			0		/* 0 : table number and name must be equal
										     1 : table number can be different
										*/
#endif

#ifdef __cplusplus
extern "C" {
#endif 

#if DB_APP_SQL_FILE > 0

typedef void (*DB_SHOWPROCESS_CALLBACK)(unsigned char);

/*
*	Application that run SQL file, SQL file format is lines of SQL sentence.
*/
extern DB_INT8 
DBAppExecuteSQLFileExt(DB_UINT8 *fnsql, DB_HANDLE* db, DB_SHOWPROCESS_CALLBACK callback, DB_UINT32 cachesz);

/*
*	Application that run SQL file, SQL file format is lines of SQL sentence.
*/
extern DB_INT8 
DBAppExecuteSQLFile(DB_UINT8 *fnsql, DB_UINT8 *DB_File_Name, DB_UINT32 cachesz);

/*
*	set SQL execute process show callback function
*/
void 
DBAppSQLExeCallbackSet(void *callback);

/*
*	clear SQL execute process show callback to null
*/
void 
DBAppSQLExeCallbackClear(void *callback);
#endif

#if DB_APP_OKF_FILE > 0
/*
*	Application that upgrade OKF file, OKF file is the old format file for system updating
*/
extern DB_INT8 
DBAppExecuteOKFFile();
#endif

#ifdef __cplusplus
}
#endif 

#endif

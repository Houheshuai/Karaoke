#ifndef _SQL_H_
#define _SQL_H_

#define MAX_SQL_STRING_LENGTH		(2 *1024)		/* maximum SQL string length */

/* SQL Symbols */

#define SQL_SYMBOL_SELECT	0							/*"SELECT"*/
#define SQL_SYMBOL_FROM	(SQL_SYMBOL_SELECT+1)		/*"FROM"*/
#define SQL_SYMBOL_WHERE	(SQL_SYMBOL_FROM+1)		/*"WHERE"*/
#define SQL_SYMBOL_ORDER	(SQL_SYMBOL_WHERE+1)		/*"ORDER"*/
#define SQL_SYMBOL_BY		(SQL_SYMBOL_ORDER+1)		/*"BY"*/
#define SQL_SYMBOL_VALUE	(SQL_SYMBOL_BY+1)			/*"VALUES"*/
#define SQL_SYMBOL_SET		(SQL_SYMBOL_VALUE+1)		/*"SET"*/
#define SQL_SYMBOL_ADD		(SQL_SYMBOL_SET+1)			/*"ADD"*/
#define SQL_SYMBOL_DROP	(SQL_SYMBOL_ADD+1)			/*"DROP"*/
#define SQL_SYMBOL_MODIFY	(SQL_SYMBOL_DROP+1)		/*"MODIFY"*/
#define SQL_SYMBOL_CHAR	(SQL_SYMBOL_MODIFY+1)		/*"CHAR"*/
#define SQL_SYMBOL_BYTE	(SQL_SYMBOL_CHAR+1)		/*"BYTE"*/
#define SQL_SYMBOL_SHORT	(SQL_SYMBOL_BYTE+1)			/*"SHORT"*/
#define SQL_SYMBOL_LONG	(SQL_SYMBOL_SHORT+1)		/*"CHAR"*/
#define SQL_SYMBOL_STRING	(SQL_SYMBOL_LONG+1)		/*"STRING"*/
#define SQL_SYMBOL_AND		(SQL_SYMBOL_STRING+1)		/*"AND"*/
#define SQL_SYMBOL_OR		(SQL_SYMBOL_AND+1)			/*"OR"*/
#define SQL_SYMBOL_INVERTED_COMMA	(SQL_SYMBOL_OR+1)					/*"'"*/
#define SQL_SYMBOL_COMMA				(SQL_SYMBOL_INVERTED_COMMA+1)		/*","*/
#define SQL_SYMBOL_LEFT_BRACKET		(SQL_SYMBOL_COMMA+1)				/*"("*/
#define SQL_SYMBOL_RIGHT_BRACKET		(SQL_SYMBOL_LEFT_BRACKET+1)		/*")"*/
#define SQL_SYMBOL_EQUAL				(SQL_SYMBOL_RIGHT_BRACKET+1)		/*"="*/
#define SQL_SYMBOL_LARGE				(SQL_SYMBOL_EQUAL+1)				/*">"*/
#define SQL_SYMBOL_LARGE_EQUAL		(SQL_SYMBOL_LARGE+1)				/*">="*/
#define SQL_SYMBOL_SMALL				(SQL_SYMBOL_LARGE_EQUAL+1)			/*"<"*/
#define SQL_SYMBOL_SMALL_EQUAL		(SQL_SYMBOL_SMALL+1)				/*"<="*/
#define SQL_SYMBOL_NOT_EQUAL			(SQL_SYMBOL_SMALL_EQUAL+1)			/*"!="*/
#define SQL_SYMBOL_NUM		(SQL_SYMBOL_NOT_EQUAL+1)		/* maximum SQL symbol number */

/* SQL Commands */

#define SQL_CMD_INSERT		0		/*"INSERT INTO"*/
#define SQL_CMD_SELECT		1		/*"SELECT"*/ 
#define SQL_CMD_UPDATE		2		/*"UPDATE"*/
#define SQL_CMD_DELETE		3		/*"DELETE FROM"*/
#define SQL_CMD_CREATE		4		/*"CREATE TABLE"*/
#define SQL_CMD_ALTER		5		/*"ALTER TABLE"*/
#define SQL_CMD_DROP		6		/*"DROP TABLE"*/
#define SQL_CMD_NUM		7		/* maximum SQL cmd number */

#define SQLCmdSymbol(symbol_id) (symbol_id >= SQL_SYMBOL_SELECT && symbol_id <= SQL_SYMBOL_MODIFY)

#define SQLBlankChar(chr)	 	((chr == ' ') || (chr == 0x09) || (chr == 0x0d)  || (chr == 0x0a))

/*
*	check operate char like ">", "<", "=", etc.
*/
#define SQLOprChar(chr) 			((chr == '>') || (chr == '<') || (chr == '=') || (chr == '!'))

#define SQLSeperateChar(chr) 	(SQLBlankChar(chr) || (chr == '(') || (chr == ')') || (chr == ','))

extern DB_UINT8 SQLCmdList[SQL_CMD_NUM][13];
/* SQL symbols */
extern DB_UINT8 SQLSymbols[SQL_SYMBOL_NUM][9];

#ifdef __cplusplus
extern "C" {
#endif 

/*
*	find symbol in sql string, and return the end point of symbol
*	@sqlstr : sql string
*	@symbol : symbol will be found in sql string
*/
extern DB_INT16 SQLStrStr(DB_UINT8 *sqlstr, DB_UINT8 *symbol);
/*
*	get first word in sql string
*	@sqlstr : sql string
*	@getword : buffer to save getword
*	@wordlen : maximum word read from sqlstr
*/
extern DB_INT16 SQLGetWord(DB_UINT8 *sqlstr, DB_UINT8 *getword, DB_INT16 wordlen);

extern DB_INT8 SQLExecute(DB_UINT8 *query, DB_HANDLE *db);

#ifdef __cplusplus
}
#endif 

#endif

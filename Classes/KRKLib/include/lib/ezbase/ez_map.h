/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_map.h
** Revision : 1.00											
**																	
** Description: c code map functions, not multi-thread safe
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by ...
**
************************ HOWTO *******************************
** 
**	call function [ez_map_new] to create a new map object
**	call function [ez_map_free] to destory a map after finish using
**	query map functions:
**		[ez_map_get]
**		[ez_map_find]
**		[ez_map_begin]
**		[ez_map_end]
**		[ez_map_size]
**	modify map functions
**		[ez_map_pushback]
**		[ez_map_insert]
**		[ez_map_append]
**		[ez_map_clear]
**		[ez_map_erase]
**
*/

#ifndef _EZMAP_H_
#define _EZMAP_H_

#include <lib/ezbase/ez_vector.h>

#define ez_map_get_key(dat)			((char*)(dat))
#define ez_map_get_value(mp,dat)	((char*)(dat)+mp->keysz)

/*
*	map base structure
*/
typedef struct {
	ezVector_t 		vt;					/* map list */
	int					keysz;			/* key data size in bytes */
	int					valuesz;			/* value data size in bytes */
	int					keytype;			/* 0 - numeric, 1 - string */
} ezMap_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_map_new
 * Arguments      	: keysz - name data size, valuesz - value data size, capacity - initialize capacity
 * Return         	: map pointer
 * Description    	: new a map
 *					
*/
extern ezMap_t* ez_map_new(int keysz, int valuesz, int capacity);

/*
 * Function name  	: ez_map_free
 * Arguments      	: map pointer
 * Return         	: none
 * Description    	: free a map
 *					
*/
extern void ez_map_free(ezMap_t* mp);

/*
 * Function name  	: ez_map_set_keytype
 * Arguments      	: mp - map handle, keytype - key type, 0 -numeric, 1 - string
 * Return         	: none
 * Description    	: set key type
 *					
*/
extern void ez_map_set_keytype(ezMap_t* mp, int keytype);

/*
 * Function name  	: ez_map_pushback
 * Arguments      	: mp - map pointer, key - key buffer address, value - value buffer address
 * Return         	: pushed node pointer
 * Description    	: push a node to end of map
 *					
*/
extern void* ez_map_pushback(ezMap_t* mp, void* key, void* value);

/*
 * Function name  	: ez_map_get
 * Arguments      	: mp - map pointer, key - key data address
 * Return         	: get value data address
 * Description    	: get the value data by key
 *					
*/
extern void* ez_map_get(ezMap_t* mp, void* key);

/*
 * Function name  	: ez_map_at
 * Arguments      	: mp - map pointer, pos - position in vector
 * Return         	: get value data address
 * Description    	: get the value data at input position 
 *					
*/
extern void* ez_map_at(ezMap_t* mp, int pos);

/*
 * Function name  	: ez_map_find
 * Arguments      	: mp - map pointer, value- value data buffer, start - search from this node
 * Return         	: found node address
 * Description    	: search a special value in map, value is duplicated, so you can find next by set "start" parameter
 *					
*/
extern void* ez_map_find(ezMap_t* mp, void* value, void* start);

/*
 * Function name  	: ez_map_erase
 * Arguments      	: mp - map pointer, key - key data address
 * Return         	: next node address
 * Description    	: erase the node by index
 *					
*/
extern void* ez_map_erase(ezMap_t* mp, void* key);

/*
 * Function name  	: ez_map_insert
 * Arguments      	: mp - map pointer, key - insert before this key, ikey - insert key, ivalue - insert value
 * Return         	: inserted node address
 * Description    	: insert a new node before key
 *					
*/
extern void* ez_map_insert(ezMap_t* mp, void* key, void* ikey, void* ivalue);

/*
 * Function name  	: ez_map_append
 * Arguments      	: mp - map pointer, key - insert after this key, ikey - insert key, ivalue - insert value
 * Return         	: new node address
 * Description    	: append a new node after key
 *					
*/
extern void* ez_map_append(ezMap_t* mp, void* key, void* ikey, void* ivalue);

/*
 * Function name  	: ez_map_clear
 * Arguments      	: mp - map pointer
 * Return         	: none
 * Description    	: clear all nodes
 *					
*/
extern void ez_map_clear(ezMap_t* mp);

/*
 * Function name  	: ez_map_begin
 * Arguments      	: vt - map pointer
 * Return         	: first node
 * Description    	: get first node address
 *					
*/
extern void* ez_map_begin(ezMap_t* mp);

/*
 * Function name  	: ez_map_end
 * Arguments      	: vt - map pointer
 * Return         	: end address of map
 * Description    	: get end of map, the return address is not a valid node in list
 *					
*/
extern void* ez_map_end(ezMap_t* mp);

/*
 * Function name  	: ez_map_size
 * Arguments      	: vt - map pointer
 * Return         	: map size 
 * Description    	: get map size
 *					
*/
extern int ez_map_size(ezMap_t* mp);

#ifdef __cplusplus
}
#endif

#endif


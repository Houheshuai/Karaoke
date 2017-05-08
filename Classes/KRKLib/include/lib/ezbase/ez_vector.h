/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_vector.h
** Revision : 1.00											
**																	
** Description: c code vector functions to simulate STL vector, not multi-thread safe
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
**	call function [ez_vector_new] to create a new vector object
**	call function [ez_vector_free] to destory a vector after finish using
**	query vector functions:
**		[ez_vector_get]
**		[ez_vector_find]
**		[ez_vector_begin]
**		[ez_vector_end]
**		[ez_vector_size]
**	modify vector functions
**		[ez_vector_pushback]
**		[ez_vector_insert]
**		[ez_vector_append]
**		[ez_vector_clear]
**		[ez_vector_erase]
**
*/

#ifndef _EZVECTOR_H_
#define _EZVECTOR_H_

/*
*	vector base structure
*/
typedef struct {
	int 		capacity;				/* vector capacity in node count*/
	int 		size;						/* vector size in node count */
	int		resize;					/* size of bytes when resize vector */
	int		nodesz;					/* node size in bytes */
	void*	userdata;				/* user data buffer address */
	
} ezVector_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_vector_init
 * Arguments      	: vt - vector handler, sz - vector node size, capacity - intialize capacity
 * Return         	: vector pointer
 * Description    	: initialize a vector
 *					
*/
extern ezVector_t* ez_vector_init(ezVector_t* vt, int sz, int capacity);

/*
 * Function name  	: ez_vector_deinit
 * Arguments      	: vector pointer
 * Return         	: none
 * Description    	: deinialize a vector
 *					
*/
extern void ez_vector_deinit(ezVector_t* vt);

/*
 * Function name  	: ez_vector_new
 * Arguments      	: sz - vector node size, capacity - intialize capacity
 * Return         	: vector pointer
 * Description    	: new a vector
 *					
*/
extern ezVector_t* ez_vector_new(int sz, int capacity);

/*
 * Function name  	: ez_vector_free
 * Arguments      	: vector pointer
 * Return         	: none
 * Description    	: free a vector
 *					
*/
extern void ez_vector_free(ezVector_t* vt);

/*
 * Function name  	: ez_vector_pushback
 * Arguments      	: vt - vector pointer, node - node buffer address
 * Return         	: pushed node pointer
 * Description    	: push a node to end of vector
 *					
*/
extern void* ez_vector_pushback(ezVector_t* vt, void* node);

/*
 * Function name  	: ez_vector_pushback_multi
 * Arguments      	: vt - vector pointer, node - node buffer address
 * Return         	: pushed node pointer
 * Description    	: push multi-count node to end of vector
 *					
*/
extern void* ez_vector_pushback_multi(ezVector_t* vt, void* node, int count);

/*
 * Function name  	: ez_vector_get
 * Arguments      	: vt - vector pointer, id - index in vector
 * Return         	: get node address
 * Description    	: get the node by index
 *					
*/
extern void* ez_vector_get(ezVector_t* vt, int id);

/*
 * Function name  	: ez_vector_find
 * Arguments      	: vt - vector pointer, node- node data buffer
 * Return         	: found node address
 * Description    	: find the node in vector
 *					
*/
extern void* ez_vector_find(ezVector_t* vt, void* node);

/*
 * Function name  	: ez_vector_find_pos
 * Arguments      	: vt - vector pointer, node- node data buffer
 * Return         	: found node position, -1 is error
 * Description    	: find the node in vector
 *					
*/
extern int ez_vector_find_pos(ezVector_t* vt, void* node);
extern int ez_vector_find_posEx(ezVector_t* vt, void* node, int(*cmp)(void* node_i, void* node));

/*
 * Function name  	: ez_vector_erase
 * Arguments      	: vt - vector pointer, id - index in vector
 * Return         	: next node address
 * Description    	: erase the node by index
 *					
*/
extern void* ez_vector_erase(ezVector_t* vt, int id);

/*
 * Function name  	: ez_vector_insert
 * Arguments      	: vt - vector pointer, id - index in vector, node - new node address
 * Return         	: new node address
 * Description    	: insert a new node before index (id)
 *					
*/
extern void* ez_vector_insert(ezVector_t* vt, int id, void* node);

/*
 * Function name  	: ez_vector_append
 * Arguments      	: vt - vector pointer, id - index in vector, node - new node address
 * Return         	: new node address
 * Description    	: append a new node after index (id)
 *					
*/
extern void* ez_vector_append(ezVector_t* vt, int id, void* node);

/*
 * Function name  	: ez_vector_clean
 * Arguments      	: vt - vector pointer
 * Return         	: none
 * Description    	: clear all nodes
 *					
*/
extern void ez_vector_clear(ezVector_t* vt);

/*
 * Function name  	: ez_vector_begin
 * Arguments      	: vt - vector pointer
 * Return         	: first node
 * Description    	: get first node address
 *					
*/
extern void* ez_vector_begin(ezVector_t* vt);

/*
 * Function name  	: ez_vector_end
 * Arguments      	: vt - vector pointer
 * Return         	: end address of vector
 * Description    	: get end of vector, the return address is not a valid node in list
 *					
*/
extern void* ez_vector_end(ezVector_t* vt);

/*
 * Function name  	: ez_vector_size
 * Arguments      	: vt - vector pointer
 * Return         	: vector size 
 * Description    	: get vector size
 *					
*/
extern int ez_vector_size(ezVector_t* vt);

/*
 * Function name  	: ez_vector_set_resize
 * Arguments      	: vt - vector pointer
 *									resize - size of resize bytes
 * Return         	: none
 * Description    	: set bytes of resize
 *					
*/
extern void ez_vector_set_resize(ezVector_t* vt, int resize);

#ifdef __cplusplus
}
#endif

#endif


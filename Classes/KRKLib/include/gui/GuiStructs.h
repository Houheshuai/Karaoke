#ifndef _GUI_STRUCTS_H_
#define _GUI_STRUCTS_H_

/*
*	UI bind Field
*/
typedef struct 
{
	int 								WinID;					/* bind UI window ID */
	int 								offset;					/* bind data offset in data structure */
	int 								type;						/* bind data type */

} bindField_t;

#endif


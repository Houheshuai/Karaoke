/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : ez_config.h
** Revision : 1.00											
**																	
** Description: config file parser
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
**
*/


#ifndef _EZCONFIG_H_
#define _EZCONFIG_H_

#include <lib/ezbase/ez_vector.h>
#include <lib/ezbase/ez_map.h>

#define EZCONFIG_STR_NAME_SZ			32
#define EZCONFIG_STR_MAX_SZ				64
#define EZCONFIG_INTVAL_MAX_SZ		16
#define EZCONFIG_FILENAME_SZ			128

enum
{
	EZCONFIG_ERR_NONE = 0,
	EZCONFIG_ERR_EOF,
	EZCONFIG_ERR_OPENFILE,
	EZCONFIG_ERR_MALLOC,
	EZCONFIG_ERR_NO_TAG,
	EZCONFIG_ERR_NO_BEGIN,
	EZCONFIG_ERR_NO_END,
	EZCONFIG_ERR_NO_NAME,
	EZCONFIG_ERR_NO_TITLE,
	EZCONFIG_ERR_NO_EQUAL,
	EZCONFIG_ERR_NO_CURRENT,
	EZCONFIG_ERR_NO_DEFAULT,
	EZCONFIG_ERR_NO_ITEMS,
	EZCONFIG_ERR_NO_ITEM,
	EZCONFIG_ERR_NO_CONFIG,
};

enum
{
	EZCONFIG_OPTION_TYPE_STR = 0,
	EZCONFIG_OPTION_TYPE_INT,
};

/*
* option item
*/
typedef struct s_ezOptionItem{
	char								name[EZCONFIG_STR_MAX_SZ];
} ezOptionItem_t;

/*
*	config node
*/
typedef struct {
	char								name[EZCONFIG_STR_NAME_SZ];		/* option name string */
	char								title[EZCONFIG_STR_MAX_SZ];			/* option title string */
	int								type;			/* 0: string type, items are valiable, 1: integer type, items are not avaliable */
	int								curval;		/* current setup value */
	int								defval;		/* default value */
	int								minval;		/* minmum value */
	int								maxval;		/* maximum value */
	int								hexfmt;		/* hex format integer */
	ezVector_t*					items;			/* items string list*/
} ezConfigNode_t;

/*
*	config handle data structure
*/
typedef struct {
	char								filename[EZCONFIG_FILENAME_SZ];				/* save config file name full path here */
	ezMap_t**					nodes;																	/* config nodes list */
	char *							confnames;														/* config name strings */
	int								count;																	/* count of config list, if support multi-language config, configcount > 1 */
	int								current;																/* current config ID */
	void*							lock;
} ezConfig_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: ez_config_new
 * Arguments      	: filename - config file name
 * Return         	: config handle pointer, NULL is error
 * Description    	: create new config file
 *					
*/
extern ezConfig_t* ez_config_new(const char* filename);

/*
 * Function name  	: ez_config_free
 * Arguments      	: opt - config handle
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: free config handle
 *					
*/
extern int ez_config_free(ezConfig_t* opt);

/*
 * Function name  	: ez_config_load
 * Arguments      	: filename - config file name , full path
 * Return         	: config handler
 * Description    	: load config data from file to memory, save in ezConfig_t structure
 *					
*/
extern ezConfig_t* ez_config_load(const char* filename);

/*
 * Function name  	: ez_config_unload
 * Arguments      	: opt - config handler, autosave - save to file
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: free config data memory 
 *					
*/
extern int ez_config_unload(ezConfig_t* opt, int autosave);

/*
 * Function name  	: ez_config_switch
 * Arguments      	: opt - config handler
 *									name - config name
 * Return         	: 0 - succ, <>0 error
 * Description    	: switch config list to another language id, for multi-language support
 *					
*/
extern int ez_config_switch(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_save
 * Arguments      	: opt - config handler
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: save configs from memory to file
 *					
*/
extern int ez_config_save(ezConfig_t* opt);

/*
 * Function name  	: ez_config_add_node
 * Arguments      	: node - config node
 *									name - new item name
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: add new item to node
 *					
*/
extern int ez_config_add_node_item(ezConfig_t* opt, ezConfigNode_t* node, const char* name);

/*
 * Function name  	: ez_config_add_node
 * Arguments      	: opt - config handler
 *									node - input new node
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: add new node to config
 *					
*/
extern int ez_config_add_node(ezConfig_t* opt, ezConfigNode_t* node);

/*
 * Function name  	: ez_config_get_value
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: >=0 option value, -1 error
 * Description    	: get option node by name
 *					
*/
extern ezConfigNode_t* ez_config_get_node(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_config_name
 * Arguments      	: opt - config handler
 * Return         	: config name string
 * Description    	: get config name string
 *					
*/
extern char* ez_config_get_config_name(ezConfig_t* opt);

/*
 * Function name  	: ez_config_get_value
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: >=0 option value, -1 error
 * Description    	: get option current value
 *					
*/
extern int ez_config_get_value(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_default
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: >=0 option value, -1 error
 * Description    	: get option default value
 *					
*/
extern int ez_config_get_default(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_min
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: >=0 option minmum value, -1 error
 * Description    	: get option minimum value, only for integer type option
 *					
*/
extern int ez_config_get_min(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_max
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: >=0 option maximum value, -1 error
 * Description    	: get option maximum value, only for integer type option
 *					
*/
extern int ez_config_get_max(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_value
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: title string address, NULL is error
 * Description    	: get option title string
 *					
*/
extern char* ez_config_get_title(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_option_name
 * Arguments      	: opt - config handler
 *									id - option index
 * Return         	: title string address, NULL is error
 * Description    	: get option name string
 *					
*/
extern char* ez_config_get_option_name(ezConfig_t* opt, int id);

/*
 * Function name  	: ez_config_get_option_items_str
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									value - option value
 * Return         	: option item string address
 * Description    	: get option item string
 *					
*/
extern char* ez_config_get_option_items_str(ezConfig_t* opt, const char* name, int value);

/*
 * Function name  	: ez_config_set_option_items_str
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									value - option value
 * Return         	: option item string address
 * Description    	: set option item string
 *					
*/
extern char* ez_config_set_option_items_str(ezConfig_t* opt, const char* name, int value, const char* valstr);

/*
 * Function name  	: ez_config_get_option_items_str
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									itemstr - item string
 * Return         	: option item string address
 * Description    	: get option item value by item string
 *					
*/
extern int ez_config_get_option_item_value(ezConfig_t* opt, const char* name, const char* itemstr);

/*
 * Function name  	: ez_config_get_option_type
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: option item string address
 * Description    	: get option name string
 *					
*/
extern int ez_config_get_option_type(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_get_option_count
 * Arguments      	: opt - config handler
 * Return         	: option count, -1 is error code
 * Description    	: get option count
 *					
*/
extern int ez_config_get_option_count(ezConfig_t* opt);

/*
 * Function name  	: ez_config_get_option_itemcount
 * Arguments      	: opt - config handler
 *									name - input option name string
 * Return         	: option items count, -1 is error code
 * Description    	: get option items count
 *					
*/
extern int ez_config_get_option_itemcount(ezConfig_t* opt, const char* name);

/*
 * Function name  	: ez_config_set_value
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									value - input option value
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: set option current value
 *					
*/
extern int ez_config_set_value(ezConfig_t* opt, const char* name, int value);

/*
 * Function name  	: ez_config_set_strvalue
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									valstr - value string
 * Return         	: new option value
 * Description    	: set option item value by item string
 *					
*/
extern int ez_config_set_strvalue(ezConfig_t* opt, const char* name, const char* valstr);

/*
 * Function name  	: ez_config_change_value
 * Arguments      	: opt - config handler
 *									name - input option name string
 *									step - input option step (-/+)
 									circle - input option if need cirlce
 * Return         	: 0 -succ, <>0 - error code
 * Description    	: set option current value
 *					
*/
extern int ez_config_change_value(ezConfig_t* opt, const char* name, int step, int circle);

#ifdef __cplusplus
}
#endif

#endif


/************************************************************************************** 
** Copyright (C) 2011 Multak,Inc. All rights reserved
**
** Filename : ez_xmlshell.h
** Revision : 1.00
**
** Author :  yexf
** Date :  2012-10-18
**
** Description: 
**************************************************************************************

				功能：解析执行脚本文件
				脚本文件定义：
				类型 1：	<node name [attribute]>value</node name>
				类型 2： <node name [attribute]>
				<child node1>value</child node1>
				<child node2>value</child node2>
				.....
				</node name>

				运行流程：
				1. ezXmlShell_Init();		初始化并解析脚本
				2. ezXmlShell_Handle();		执行脚本
				3. ezXmlShell_DeInit();		释放内存

				如果需要执行特定动作，可以将node name 与 函数指针绑定
				函数指针类型：typedef void (*handle_xml_node)(struct tagezXmlNode_t *,void *);
				例如copy动作定义如下：
				<copy>
				[<type>file | dir</type>]
				<src>filepath | dirpath</src>
				<dst>filepath | dirpath</dst>
				</copy>
				函数声明为void funcname(struct tagezXmlParse_t*pnode,void *userdata)；
				userdata用户可以通过ezXmlShell_SetUserdata设置
				通过ezXmlShell_SearchChildNode，  ezXmlShell_Get*** 获取所需的参数
				通过 ezXmlShell_SetHandle(xmlshell,node name,funcname)绑定
				
**************************************************************************************/ 

#ifndef _EZ_XMLSHELL_H_
#define _EZ_XMLSHELL_H_

#define NODEMAX				64
#define FILENAME_SZ			128

#define NAME_SZ				64
#define VALUE_SZ			128

enum xml_parse_type
{
	PARSE_XML_ERR = 0,
	PARSE_XML_HEAD,
	PARSE_XML_NOTE,
	PARSE_ELE_START,
	PARSE_ELE_END,
	PARSE_ELE_PDATA,
	PARSE_ELE_NDATA,
	PARSE_COUNT,
};
typedef struct tagezXmlNode_Attr ezXmlNode_Attr;
struct tagezXmlNode_Attr
{
	char *name;
	char *value;
	ezXmlNode_Attr *next;
};

typedef struct tagezXmlNode_t ezXmlNode_t;
typedef int (*handle_xml_node)(ezXmlNode_t *,void *);
typedef handle_xml_node hxn;

struct tagezXmlNode_t
{
	char*						strName;		//节点名
	char*						strValue;		//节点值
	char*						strAttr;		//结点属性
	
	int							nChild;			//子节点个数
	hxn							handle;			//处理器
	
	ezXmlNode_Attr*				tAttr;			//属性

	struct tagezXmlNode_t*		pNext;			//子节点
	struct tagezXmlNode_t*		pFather;		//父节点
};

typedef struct tagezXmlParse_t ezXmlParse_t;
typedef void (*ezXmlParseHandle)(ezXmlParse_t *);
typedef ezXmlParseHandle xph;
typedef void (*ezXmlParseAttrFree)(ezXmlNode_Attr *);
typedef ezXmlParseAttrFree xpaf;
typedef ezXmlNode_Attr *(*ezXmlParseAttr)(ezXmlParse_t *,const char *);
typedef ezXmlParseAttr xpa;


struct tagezXmlParse_t 
{
	xpaf				attr_parse_free;
	xpa					attr_parse;
	xph					parse_handle;
	xph					handle[PARSE_COUNT];
	void				*userdata;
	char *				xml_str;
	char *				xml_cur;
	char *				xml_ret;
	int					ret_type;
};

typedef struct {
	char				filename[FILENAME_SZ];		/* save config file name full path here */
	ezXmlNode_t			root;
	int					nxml_str;
	char				*xml_str;
	ezXmlParse_t			parse;
	void				*userdata;
} ezXmlShell_t;
#ifdef __cplusplus
extern "C" {
#endif
	/********************************************************************************************* 
	** Function name  : *ezXmlNode_SearchAttr
	** Arguments      : pnode - 
	**                  name - 
	** Return         : char 
	** Date&Time      : 2012-11-12
	** Description    : 
	*********************************************************************************************/ 
	char *ezXmlShell_SearchAttr(ezXmlNode_t *pnode,const char *name);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_GetAttr
	** Arguments      : pnode - 
	** Return         : char 
	** Date&Time      : 2012-10-18  
	** Description    : 返回节点属性 如果没有返回NULL
	*********************************************************************************************/ 
	ezXmlNode_Attr *ezXmlShell_GetAttr(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_GetName
	** Arguments      : pnode - 
	** Return         : char 
	** Date&Time      : 2012-10-18  
	** Description    : 返回节点名 如果没有返回NULL
	*********************************************************************************************/ 
	char *ezXmlShell_GetName(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_GetValue
	** Arguments      : pnode - 
	** Return         : char 
	** Date&Time      : 2012-10-18  
	** Description    : 返回节点的value值 如果没有返回NULL
	*********************************************************************************************/ 
	char *ezXmlShell_GetValue(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : ezXmlShell_SetHandle
	** Arguments      : pxml - 解析器
	**                  name - 节点名
	**                  handle - 执行的动作
	** Return         : int 
	** Date&Time      : 2012-10-18  
	** Description    : 通过给定节点名绑定指定节点执行的动作
	*********************************************************************************************/ 
	int ezXmlShell_SetHandle(ezXmlShell_t *pxml,char *name,hxn handle);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchChildNode
	** Arguments      : pfather - 
	**                  name - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-10-18  
	** Description    : 通过给定子节点名查找指定节点的子节点 如果没有返回NULL
	*********************************************************************************************/ 
	ezXmlNode_t *ezXmlShell_SearchChildNode(ezXmlNode_t *pfather,char *name);
	
	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchNode
	** Arguments      : pfather - 
	**                  name - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-10-18  17:48:27
	** Description    : 通过节点名查找节点 如果没有返回NULL
	*********************************************************************************************/ 
	ezXmlNode_t *ezXmlShell_SearchNode(ezXmlShell_t *pxml,char *name);
	
	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchNode_Index
	** Arguments      : pfather - 
	**                  name - 
	**                  index - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-12-06
	** Description    : 
	*********************************************************************************************/ 
	ezXmlNode_t *ezXmlShell_SearchNode_Index(ezXmlNode_t *pfather,char *name,int index);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchChildNext
	** Arguments      : pfather - 
	**                  pos - 
	**                  name - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-11-12
	** Description    : 
	*********************************************************************************************/ 
	ezXmlNode_t *ezXmlShell_SearchChildNext(ezXmlNode_t *pfather,ezXmlNode_t *pos,char *name);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_ChildNodeNum
	** Arguments      : pfather - 
	**                  name - 
	** Return         : int 
	** Date&Time      : 2012-11-12
	** Description    : 
	*********************************************************************************************/ 
	int ezXmlShell_ChildNodeNum(ezXmlNode_t *pfather,char *name);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_SetUserdata
	** Arguments      : pxml - 
	**                  userdata - 
	** Return         : void 
	** Date&Time      : 2012-10-18
	** Description    : 设置用户数据
	*********************************************************************************************/ 
	void ezXmlShell_SetUserdata(ezXmlShell_t *pxml,void *userdata);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_Handle
	** Arguments      : pxml - 
	** Return         : 0 -succ, <>0 - err code 
	** Date&Time      : 2012-10-18  
	** Description    : 执行脚本动作
	*********************************************************************************************/ 
	int ezXmlShell_Handle(ezXmlShell_t *pxml);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_DeInit
	** Arguments      : pxml - 
	** Return         : void 
	** Date&Time      : 2012-10-18  
	** Description    : 释放内存
	*********************************************************************************************/ 
	void ezXmlShell_DeInit(void *pxml);
	
	/********************************************************************************************* 
	** Function name  : *ezXmlShell_Init
	** Arguments      : filename - 
	** Return         : ezXmlShell_t 
	** Date&Time      : 2012-10-18  17:48:36
	** Description    : 装载脚本并初始化解析器
	*********************************************************************************************/ 
	ezXmlShell_t *ezXmlShell_InitMem(void *pmem,int len);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_Init
	** Arguments      : filename - 
	** Return         : ezXmlShell_t 
	** Date&Time      : 2012-10-18  
	** Description    : 装载脚本文件并初始化解析器
	*********************************************************************************************/ 
	ezXmlShell_t *ezXmlShell_Init(const char *filename);
#ifdef __cplusplus
}
#endif

#endif


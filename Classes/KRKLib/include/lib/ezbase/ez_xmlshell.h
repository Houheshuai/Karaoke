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

				���ܣ�����ִ�нű��ļ�
				�ű��ļ����壺
				���� 1��	<node name [attribute]>value</node name>
				���� 2�� <node name [attribute]>
				<child node1>value</child node1>
				<child node2>value</child node2>
				.....
				</node name>

				�������̣�
				1. ezXmlShell_Init();		��ʼ���������ű�
				2. ezXmlShell_Handle();		ִ�нű�
				3. ezXmlShell_DeInit();		�ͷ��ڴ�

				�����Ҫִ���ض����������Խ�node name �� ����ָ���
				����ָ�����ͣ�typedef void (*handle_xml_node)(struct tagezXmlNode_t *,void *);
				����copy�����������£�
				<copy>
				[<type>file | dir</type>]
				<src>filepath | dirpath</src>
				<dst>filepath | dirpath</dst>
				</copy>
				��������Ϊvoid funcname(struct tagezXmlParse_t*pnode,void *userdata)��
				userdata�û�����ͨ��ezXmlShell_SetUserdata����
				ͨ��ezXmlShell_SearchChildNode��  ezXmlShell_Get*** ��ȡ����Ĳ���
				ͨ�� ezXmlShell_SetHandle(xmlshell,node name,funcname)��
				
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
	char*						strName;		//�ڵ���
	char*						strValue;		//�ڵ�ֵ
	char*						strAttr;		//�������
	
	int							nChild;			//�ӽڵ����
	hxn							handle;			//������
	
	ezXmlNode_Attr*				tAttr;			//����

	struct tagezXmlNode_t*		pNext;			//�ӽڵ�
	struct tagezXmlNode_t*		pFather;		//���ڵ�
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
	** Description    : ���ؽڵ����� ���û�з���NULL
	*********************************************************************************************/ 
	ezXmlNode_Attr *ezXmlShell_GetAttr(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_GetName
	** Arguments      : pnode - 
	** Return         : char 
	** Date&Time      : 2012-10-18  
	** Description    : ���ؽڵ��� ���û�з���NULL
	*********************************************************************************************/ 
	char *ezXmlShell_GetName(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_GetValue
	** Arguments      : pnode - 
	** Return         : char 
	** Date&Time      : 2012-10-18  
	** Description    : ���ؽڵ��valueֵ ���û�з���NULL
	*********************************************************************************************/ 
	char *ezXmlShell_GetValue(ezXmlNode_t *pnode);

	/********************************************************************************************* 
	** Function name  : ezXmlShell_SetHandle
	** Arguments      : pxml - ������
	**                  name - �ڵ���
	**                  handle - ִ�еĶ���
	** Return         : int 
	** Date&Time      : 2012-10-18  
	** Description    : ͨ�������ڵ�����ָ���ڵ�ִ�еĶ���
	*********************************************************************************************/ 
	int ezXmlShell_SetHandle(ezXmlShell_t *pxml,char *name,hxn handle);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchChildNode
	** Arguments      : pfather - 
	**                  name - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-10-18  
	** Description    : ͨ�������ӽڵ�������ָ���ڵ���ӽڵ� ���û�з���NULL
	*********************************************************************************************/ 
	ezXmlNode_t *ezXmlShell_SearchChildNode(ezXmlNode_t *pfather,char *name);
	
	/********************************************************************************************* 
	** Function name  : *ezXmlShell_SearchNode
	** Arguments      : pfather - 
	**                  name - 
	** Return         : ezXmlNode_t 
	** Date&Time      : 2012-10-18  17:48:27
	** Description    : ͨ���ڵ������ҽڵ� ���û�з���NULL
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
	** Description    : �����û�����
	*********************************************************************************************/ 
	void ezXmlShell_SetUserdata(ezXmlShell_t *pxml,void *userdata);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_Handle
	** Arguments      : pxml - 
	** Return         : 0 -succ, <>0 - err code 
	** Date&Time      : 2012-10-18  
	** Description    : ִ�нű�����
	*********************************************************************************************/ 
	int ezXmlShell_Handle(ezXmlShell_t *pxml);
	
	/********************************************************************************************* 
	** Function name  : ezXmlShell_DeInit
	** Arguments      : pxml - 
	** Return         : void 
	** Date&Time      : 2012-10-18  
	** Description    : �ͷ��ڴ�
	*********************************************************************************************/ 
	void ezXmlShell_DeInit(void *pxml);
	
	/********************************************************************************************* 
	** Function name  : *ezXmlShell_Init
	** Arguments      : filename - 
	** Return         : ezXmlShell_t 
	** Date&Time      : 2012-10-18  17:48:36
	** Description    : װ�ؽű�����ʼ��������
	*********************************************************************************************/ 
	ezXmlShell_t *ezXmlShell_InitMem(void *pmem,int len);

	/********************************************************************************************* 
	** Function name  : *ezXmlShell_Init
	** Arguments      : filename - 
	** Return         : ezXmlShell_t 
	** Date&Time      : 2012-10-18  
	** Description    : װ�ؽű��ļ�����ʼ��������
	*********************************************************************************************/ 
	ezXmlShell_t *ezXmlShell_Init(const char *filename);
#ifdef __cplusplus
}
#endif

#endif


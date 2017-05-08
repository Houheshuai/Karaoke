/*********************************************************************
**																	
**  Copyright (C) 2011 Multak,Inc.									
**  All rights reserved												
**        Filename : edb.c/ Project: EDB							
**        Revision : 1.31											
**																	
**   Note: Apply API to control database.		
**
**								Author: liwj	
**														2006.4		
*********************************************************************/

/**************��ʽ����******************
Select <��ѯ>
From <���ʽ��ͼ��> 
Where <��ѯ>
Order by<��ѯ> 
*****************************************/

/* 
<��ѯ> ::= <��ѯ���ʽ> [, <��ѯ���ʽ>]
<��ѯ���ʽ> ::= <���ʽ> [AS <����>]
<���ʽ> ::= <����> | <�ֶ�> | <����> | <���ʽ> <����> <���ʽ>
 <����> ::= <������>([<���ʽ>[,<���ʽ>]])
 <�ֶ�> 
 <����> ::= ���� | �ַ���
 <����> ::= < | > | >= | <= | = | != 
 <����>
*/

/**************��������******************
*��func(a,b)Ϊ����func����Ϊ�����ĸ����
*����aΪ���ӣ�b��a���ֵ�
*ִ��ʱ�����������ԭ�����ִ��������
****************************************/
#ifndef _ANLY_H_
#define _ANLY_H_

//#define PC_DEBUG


#define ANALYSE_ERR		0xffff
#define NO_INDEX		0xff
#define OPERATE_ERR		0xff
#define EXCUTE_ERR		0xffff

#define MAX_NODE_COUNT		255
#define MAX_TREE_COUNT		64
#define DB_MAX_SELECT_STR_SZ		256
#define MAX_OPERATE_SYMBOL	10
#define MAX_PARAM_COUNT		4

#define OPERATION_SYM_BEGIN	WT_END
#define OPERATION_SYM_END		WT_NE

#define WT_END		0
#define WT_COMMA	1
#define WT_LT		2
#define WT_GT		3
#define WT_EQ		4
#define WT_LE		5
#define WT_GE		6
#define WT_NE		7
#define WT_LB		8
#define WT_RB		9
#define WT_BYTE		10
#define WT_WORD	11
#define WT_DWORD	12
#define WT_STRING	13
#define WT_DSTRING	14
#define WT_SYMBOL	15
#define WT_FIELD	16
#define WT_FUNC		17
#define WT_ALIAS	18
#define WT_ERR		0xff



//���ʽ����ֵ���Ͷ���
#define ETR_BYTE    	WT_BYTE
#define ETR_WORD    	WT_WORD
#define ETR_DWORD	WT_DWORD
#define ETR_STRING  	WT_STRING
#define ETR_DSTRING	WT_DSTRING

//���ʽ����
#define ET_CONST	0
#define ET_LT		WT_LT		
#define ET_GT		WT_GT		
#define ET_EQ		WT_EQ		
#define ET_LE		WT_LE		
#define ET_GE		WT_GE		
#define ET_NE		WT_NE		
#define ET_BYTE		WT_BYTE
#define ET_WORD		WT_WORD
#define ET_DWORD	WT_DWORD
#define ET_STRING	WT_STRING
#define ET_FUNC		WT_FUNC
#define ET_FIELD		WT_FIELD


//��ֵ�Ƚ�����
#define ETC_INT_EQUAL		SQL_SYMBOL_EQUAL
#define ETC_INT_UNEQUAL		SQL_SYMBOL_NOT_EQUAL
#define ETC_INT_SMALL		SQL_SYMBOL_SMALL
#define ETC_INT_SMALL_EQUAL	SQL_SYMBOL_SMALL_EQUAL
#define ETC_INT_LARGE		SQL_SYMBOL_LARGE
#define ETC_INT_LARGE_EQUAL	SQL_SYMBOL_LARGE_EQUAL

#define ECT_TYPE_OFFSET		6
//�ַ����Ƚ�����
#define ETC_STR_EQUAL		ETC_INT_EQUAL + ECT_TYPE_OFFSET
#define ETC_STR_UNEQUAL		ETC_INT_UNEQUAL + ECT_TYPE_OFFSET
#define ETC_STR_SMALL		ETC_INT_SMALL + ECT_TYPE_OFFSET 
#define ETC_STR_SMALL_EQUAL	ETC_INT_SMALL_EQUAL + ECT_TYPE_OFFSET 
#define ETC_STR_LARGE		ETC_INT_LARGE + ECT_TYPE_OFFSET
#define ETC_STR_LARGE_EQUAL ETC_INT_LARGE_EQUAL + ECT_TYPE_OFFSET

typedef struct  
{
	DB_UINT8 ExperType; //���ʽ����

	DB_UINT8 ExpRetValueType;//���ʽ����ֵ����

	union
	{
		DB_UINT8 FuncType;	 //��������
		DB_UINT8 Field[DB_MAX_SELECT_STR_SZ]; //�ֶ�����
	}ConText;			//���ʽ��
	
	union 
	{
		DB_UINT8 databyte;
		DB_UINT16 dataword;
		DB_UINT32 datadword;
		DB_UINT8 datastr[DB_MAX_SELECT_STR_SZ];
	}Data;//���ʽ����ֵ

	DB_UINT8 Index; // field index
}EXPREISSION;// ���ʽ

typedef struct 
{
	DB_UINT16 ParentNodeIndex;//����������
	
	DB_UINT16 ChildNodeIndex; //�ӽ�������
	
	DB_UINT16 BrotherNodeIndex;//�ֵܽ�������

	EXPREISSION Expression; //���ʽ

}EXPREISSION_NODE;// ���ʽ���

typedef struct 
{
	DB_UINT16 RootNodeIndex;			 //�����ڵ�������

	DB_UINT8 Alias[DB_MAX_SELECT_STR_SZ]; //����

}INQUIRE_TREE;	//��ѯ��


typedef struct
{
	INQUIRE_TREE InquireTree[MAX_TREE_COUNT];

	DB_UINT8 CurrentTreeCount;	//��ǰɭ������������
}INQUIRE_FOREST;

typedef struct
{
	DB_UINT8 TokenType;
	DB_UINT8 TokenStr[DB_MAX_SELECT_STR_SZ];
}TOKEN;
	
#ifdef __cplusplus
extern "C" {
#endif 

extern DB_UINT8 AddKeyByFieldForest(DB_HANDLE *db,
						TABLE_HANDLE* TableSrc,
						TABLE_HANDLE* TableDest, 
						INQUIRE_FOREST* FieldForest, 
						INQUIRE_FOREST* ConditionForest);

extern DB_UINT8 
AddRecordByConditionForest(DB_HANDLE *db,
						TABLE_HANDLE* TableSrc,
						TABLE_HANDLE* TableDest, 
						INQUIRE_FOREST* FieldForest, 
						INQUIRE_FOREST* ConditionForest);

extern DB_UINT16 AnalyseInquire(INQUIRE_FOREST* InquireForest, DB_UINT8 *InputString, DB_UINT8 *CharCount);
extern  DB_UINT16 ExcuteTree(DB_UINT16 RootNodeIndex, DB_HANDLE *Db, TABLE_HANDLE* Table);
extern  DB_UINT16 ExecuteForest(INQUIRE_FOREST * InquireForest, DB_HANDLE* db, TABLE_HANDLE* table);

extern  DB_UINT8 GetFiledNameByIndex(DB_UINT16 NodeIndex, DB_UINT8* FieldName);
extern  DB_UINT32 GetIntgerDataByIndex(DB_UINT16 NodeIndex);
extern  DB_UINT16 GetStrDataByIndex(DB_UINT16 NodeIndex, DB_UINT8* OutPutStr);

extern  DB_UINT8 GetRetValueTypeByIndex(DB_UINT16 NodeIndex);
extern  DB_UINT8 GetExpressionType(DB_UINT16 NodeIndex);
extern  DB_UINT16 GetChildIndex(DB_UINT16 NodeIndex);

extern  DB_UINT16 GetBrotherIndex(DB_UINT16 NodeIndex);

extern void InitForest(INQUIRE_FOREST* InquireForest);

#ifdef __cplusplus
}
#endif 

#endif

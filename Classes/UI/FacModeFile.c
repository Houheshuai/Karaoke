#include "FacModeFile.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_TAG_LEN	32
#define MAX_VAL_LEN	32

typedef struct tagFM_info
{
	char tag[MAX_TAG_LEN];
	char value[MAX_TAG_LEN];
	struct tagFM_info* next;
}FM_info;

typedef struct tagListInfo
{
	FM_info* head;
	//
}ListInfo;

FM_Handle FM_init(const char* fileName)
{
	ListInfo* handle = NULL;
	FM_info* pNode;
	FILE* fp;
	char buffer[256];
	fp = fopen(fileName, "rb");
	if(fp == NULL)
		return NULL;
	while(fgets(buffer, sizeof(buffer), fp))
	{
		FM_info* info = NULL;
		char* p = buffer;
		char* tagStart = NULL;
		char* tagEnd = NULL;
		while(*p != '\0')
		{
			switch(*p)
			{
			case '<':
				if(tagStart == NULL)
					tagStart = p;
				break;
			case '>':
				if(tagEnd == NULL)
					tagEnd = p;
				break;
			case '\r':
			case '\n':
			case ';':
				*p-- = '\0';
				break;
			}
			++p;
		}
		if(tagStart != NULL && tagEnd != NULL)
		{
			int tagLen = tagEnd - tagStart - 1;
			info = (FM_info*)malloc(sizeof(FM_info));
			memcpy(info->tag, tagStart + 1, tagLen), info->tag[tagLen] = '\0';
			strcpy(info->value, tagEnd + 1);
			info->next = NULL;
			if(handle == NULL)
			{
				handle = (ListInfo*)malloc(sizeof(ListInfo));
				handle->head = info;
			}
			else
			{
				pNode->next = info;
			}
			pNode = info;
		}
	}
	fclose(fp);
	return handle;
}

static const char* searchList(const char* tag, FM_info* head)
{
	if(strcmp(tag, head->tag) == 0)
	{
		return head->value;
	}
	else if(head->next != NULL)
	{
		return searchList(tag, head->next);
	}
	else
		return NULL;
}

const char* FM_getValue(const char* tag, FM_Handle handle)
{
	if(handle->head == NULL)
		return NULL;
	return searchList(tag, handle->head);
}

static void destroyList(FM_info* pNode)
{
	if(pNode->next != NULL)
		destroyList(pNode->next);
	free(pNode);
}

void FM_deinit(FM_Handle handle)
{
	if(handle->head != NULL)
		destroyList(handle->head);
	free(handle);
}
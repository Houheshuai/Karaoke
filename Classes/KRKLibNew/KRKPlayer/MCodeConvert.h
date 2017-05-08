#ifndef MCODECONVERT_H
#define MCODECONVERT_H

#include <stdio.h>
#include <string.h>
#include "CEGUIString.h"
#include "iconv.h"

extern void GetShouPin(unsigned char *input, unsigned char *shoupin);

extern int GetWordsCount(char *GBString);

extern int MCodeConvert_UTF8toGB2312(char* in_utf8,char* out_gb2312, int Len1,int Len2);

extern int MCodeConvert_GB2312toUTF8(char* in_gb2312,char* out_utf8, int Len1,int Len2);

extern int MCodeConvert_GB2312toUCS2(char* in_gb2312,char* out_ucs2, int Len1,int Len2);

extern int MCodeConvert_UCS2toUTF8Code(char* in_ucs2, char* out_utf8, int Len1, int Len2);
extern int UTF8toUCS2Code(CEGUI::String utf8_code, unsigned short* ucs2_code, int Len1,int *Len2);
extern int UTF8toUCS2Code2(char *utf8_code, unsigned short* ucs2_code, int Len1,int *Len2);

extern int MCodeConvert_UCS2toGB2312(char* in_ucs2, char* out_gb2312, int Len1,int Len2);

extern int multak_utf8_wcslen(CEGUI::String utf8_code);

extern unsigned char UCS2toUTF8Code(unsigned short ucs2_code, unsigned char* utf8_code);

int MCodeConvertAPI(const char* from_charset, const char *to_charset, char* in_buffer, char* out_buffer, int Len1, int Len2);

int isNotHead(unsigned char b);   //......
unsigned short makeChar(int b1, int b2);  //.....

class CodeConverter
{
private:
	iconv_t cd;
public:
	// 
	CodeConverter(const char *from_charset, const char *to_charset)
	{
		cd = iconv_open(to_charset, from_charset);
	}
	//
	~CodeConverter()
	{
			iconv_close(cd);
		}
	//
	int convert(const char *inbuf,int *inlen,char *outbuf,int *outlen)
	{
		const char **pin = &inbuf;
		char **pout = &outbuf;
		memset(outbuf, 0, (*outlen));
		return iconv(cd, pin, (size_t *)inlen, pout,(size_t *)outlen);
	}
};


#endif

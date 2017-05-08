/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : charset_iconv.h
** Revision : 1.00											
**																	
** Description:  iconv charset converter
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
*/

#ifndef CHARSET_ICONV_H
#define CHARSET_ICONV_H

/*
* charset code page list
*/
typedef enum
{
	KRK_CHARSET_GB2312  = 0,       // ��������
	KRK_CHARSET_UTF8       ,       // utf8
	KRK_CHARSET_UTF16BE    ,       // utf16be
	KRK_CHARSET_UTF16LE    ,       // utf16le
	KRK_CHARSET_BIG5       ,       // ��������
	KRK_CHARSET_GBK        ,       // ����
	KRK_CHARSET_SJIS       ,       // ����
	KRK_CHARSET_EUC_JP     ,       // ����, �ݲ�֧��
	KRK_CHARSET_EUC_KR     ,       // ����
	KRK_CHARSET_KIO8_R     ,       // ����
	KRK_CHARSET_ISO_8859_1 ,       // cp1252.��ŷ����
	KRK_CHARSET_ISO_8859_2 ,       // ��ŷ����
	KRK_CHARSET_ISO_8859_3 ,       // ��ŷ����
	KRK_CHARSET_ISO_8859_4 ,       // ��ŷ����
	KRK_CHARSET_ISO_8859_5 ,       // �������ĸ
	KRK_CHARSET_ISO_8859_6 ,       // ��������
	KRK_CHARSET_ISO_8859_7 ,       // ϣ����
	KRK_CHARSET_ISO_8859_8 ,       // ϣ������, �ݲ�֧��
	KRK_CHARSET_ISO_8859_9 ,       // cp1254����������
	KRK_CHARSET_ISO_8859_10,       // ��ŷ˹������ά����ϵ
	KRK_CHARSET_ISO_8859_11,       // ̩��, �ݲ�֧��
	KRK_CHARSET_ISO_8859_12,       // ����, �ݲ�֧��
	KRK_CHARSET_ISO_8859_13,       // ���޵ĺ���ϵ
	KRK_CHARSET_ISO_8859_14,       // ����������ϵ
	KRK_CHARSET_ISO_8859_15,       // ��չ�˷���ͷ��������ŷ��ϵ
	KRK_CHARSET_ISO_8859_16,       // ��չ�Ķ���ŷ��ϵ, �ݲ�֧��
	KRK_CHARSET_CP874      ,       // ̩��
	KRK_CHARSET_CP1250     ,       // ��ŷ
	KRK_CHARSET_CP1251     ,       // �������
	KRK_CHARSET_CP1253     ,       // ϣ����, �ݲ�֧��
	KRK_CHARSET_CP1255     ,       // ϣ������
	KRK_CHARSET_CP1256     ,       // ��������, �ݲ�֧��
	KRK_CHARSET_CP1257     ,       // ���޵ĺ���, �ݲ�֧��
	KRK_CHARSET_CP1258     ,       // Խ��, �ݲ�֧��
	KRK_CHARSET_CP1252     ,       // ��ŷ���ԡ�cp1252��iso-8859-1�ĳ���
	KRK_CHARSET_CP1254     ,       // �������cp1254��iso-8859-9�ĳ���

	KRK_CHARSET_UNICODE,

	KRK_CHARSET_UNKNOWN = -1       // always the last one

} krk_charset_et;

#define krk_gb_to_utf8(gb, gblen, utf8, utf8len)			krk_charset_convert(KRK_CHARSET_GB2312, KRK_CHARSET_UTF8, gb, utf8, gblen, utf8len)
#define krk_utf8_to_gb(utf8, utf8len, gb, gblen)			krk_charset_convert(KRK_CHARSET_UTF8, KRK_CHARSET_GB2312, utf8, gb, utf8len, gblen)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function name  	: krk_charset_convert
 * Arguments      	: in_cp - input string code page
 *									out_cp - output string code page
 *									in_str - input string
 *									out_str - output string
 *									in_len - input string length
 *									out_len - output string buffer length
 * Return         	: output string length
 * Description    	: convert string from one charset to another
 *					
*/
extern 	int krk_charset_convert(int in_cp, int out_cp, const char* in_str, char* out_str, int in_len, int out_len);

#ifdef __cplusplus
}
#endif

#endif

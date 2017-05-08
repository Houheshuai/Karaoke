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
	KRK_CHARSET_GB2312  = 0,       // 简体中文
	KRK_CHARSET_UTF8       ,       // utf8
	KRK_CHARSET_UTF16BE    ,       // utf16be
	KRK_CHARSET_UTF16LE    ,       // utf16le
	KRK_CHARSET_BIG5       ,       // 繁体中文
	KRK_CHARSET_GBK        ,       // 中文
	KRK_CHARSET_SJIS       ,       // 日文
	KRK_CHARSET_EUC_JP     ,       // 日文, 暂不支持
	KRK_CHARSET_EUC_KR     ,       // 韩文
	KRK_CHARSET_KIO8_R     ,       // 俄文
	KRK_CHARSET_ISO_8859_1 ,       // cp1252.西欧语言
	KRK_CHARSET_ISO_8859_2 ,       // 中欧语言
	KRK_CHARSET_ISO_8859_3 ,       // 南欧语言
	KRK_CHARSET_ISO_8859_4 ,       // 北欧语言
	KRK_CHARSET_ISO_8859_5 ,       // 西里尔字母
	KRK_CHARSET_ISO_8859_6 ,       // 阿拉伯语
	KRK_CHARSET_ISO_8859_7 ,       // 希腊语
	KRK_CHARSET_ISO_8859_8 ,       // 希伯来语, 暂不支持
	KRK_CHARSET_ISO_8859_9 ,       // cp1254，土耳其语
	KRK_CHARSET_ISO_8859_10,       // 北欧斯堪的纳维亚语系
	KRK_CHARSET_ISO_8859_11,       // 泰语, 暂不支持
	KRK_CHARSET_ISO_8859_12,       // 梵文, 暂不支持
	KRK_CHARSET_ISO_8859_13,       // 波罗的海语系
	KRK_CHARSET_ISO_8859_14,       // 凯尔特人语系
	KRK_CHARSET_ISO_8859_15,       // 扩展了法语和芬兰语的西欧语系
	KRK_CHARSET_ISO_8859_16,       // 扩展的东南欧语系, 暂不支持
	KRK_CHARSET_CP874      ,       // 泰文
	KRK_CHARSET_CP1250     ,       // 中欧
	KRK_CHARSET_CP1251     ,       // 西里尔文
	KRK_CHARSET_CP1253     ,       // 希腊文, 暂不支持
	KRK_CHARSET_CP1255     ,       // 希伯来文
	KRK_CHARSET_CP1256     ,       // 阿拉伯文, 暂不支持
	KRK_CHARSET_CP1257     ,       // 波罗的海文, 暂不支持
	KRK_CHARSET_CP1258     ,       // 越南, 暂不支持
	KRK_CHARSET_CP1252     ,       // 西欧语言。cp1252是iso-8859-1的超集
	KRK_CHARSET_CP1254     ,       // 土耳其语。cp1254是iso-8859-9的超集

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

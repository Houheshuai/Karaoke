/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : krk_define.h
** Revision : 1.00											
**																	
** Description: useful common functions
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

#ifndef _KRK_COMMON_H_
#define _KRK_COMMON_H_

typedef enum
{
	// file type
	MUKFileType_MP3 = 4,
	MUKFileType_AVI = 5,
	MUKFileType_OKF = 6,
	MUKFileType_MPG= 7,
	MUKFileType_CDG= 0x80,
	MUKFileType_CDS = 0x81,
	MUKFileType_VDS = 0x82,
	MUKFileType_KDS = 0x83,
	MUKFileType_ODS = 0x84,
	MUKFileType_PDS = 0x85,
	MUKFileType_ADS = 0x86,
	MUKFileType_MP4 = 0x87,
	MUKFileType_MKV = 0x88,
	MUKFileType_VOB = 0x89,
	MUKFileType_MUKMSN = 0xFD,
	MUKFileType_MUKFree = 0xFE,
	MUKFileType_MUK = 0xff,
} MUKFileType_t;

typedef enum
{
	// sub file type
	MUKSubFileType_MIDI = 1,
	MUKSubFileType_MIDIMP3 = 2,
	MUKSubFileType_KSC = 3,
	
	MUKSubFileType_CDG = 4,
	MUKSubFileType_LRC = 5,
	MUKSubFileType_KSC_TEXT = 6,
	MUKSubFileType_LYC = 7,

} MUKSubFileType_t;

/*
* multak font language type
*/
typedef enum
{
	L_CHN = 0x0000,
	L_ENG,
	L_KOR,
	L_THA,
	L_VIE,
	L_JAP,
	L_WST,
	L_RUS,
	L_DAN,
	L_OTH,
	L_XLE,
	L_JIS,
	L_FANWEN,
	L_POL,		// Polish
	L_BUR,		// Burmese
	L_DAI,		// dai wen
	L_MON,		// Mongolian 
	L_TUR,		// Turkish 
	L_ARAB,	// arab


	L_BENGALI = 0xF0,
	L_GURMUKHI,
	L_GUJARATI,
	L_ORIYA,
	L_TAMIL,
	L_TELUGU,
	L_KANNADA,
	L_MALAYALAM,
	L_SINHALA,
	
	MAX_LANTYPE
	
} krk_font_language_t;

/*
* multak song language type
*/
typedef enum
{
	SONG_CHN = 1,
	SONG_ENG = 4,
	SONG_JAP = 5,
	SONG_KOR = 6,
	SONG_VN = 7,
	SONG_THA = 8,
	SONG_RU = 9,
	SONG_BRA = 10,
	SONG_SPA = 11,
	SONG_PHI = 12,
	SONG_ITA = 13,
	SONG_GER = 14,
	SONG_FRA = 15,
	SONG_POR = 16,
	SONG_LATIN = 17,
	SONG_INI = 18,/*"印尼文","IN",*/
	SONG_JIS = 19,/*"日文","JP",*/
	SONG_XLE = 20,/*"俄文","RU",*/
	SONG_HOL = 21,/*"荷兰文","HOLLAND",*/
	SONG_INDU = 22,/*"印度文","INDIAN",*/
	SONG_INDI = 23,/*"印地文","INDOIRANIA",*/
	SONG_PERS = 24,/*"阿拉伯文","PERSIAN",*/
	SONG_HEB = 25,/*"希伯来文","HEBREW",*/
	SONG_POL = 26,/*"波兰文","POLAND",*/
	SONG_BEN = 27,/*"孟加拉文","BENGALI",*/
	
	SONG_Bhajans = 28,

	SONG_Malaysia = 29,/**/
	SONG_BGD = 30,/*孟加拉文*/
	SONG_MALA = 31,/*Malayalam文*/
	SONG_MMR = 32,/*缅甸文*/
	SONG_DaiWen = 33,/*傣文*/
	SONG_KHM = 34,/*柬埔寨文*/
	SONG_MON = 35,/*蒙古文*/
	SONG_ARAB = 36,/*阿拉伯文*/
	SONG_TUR = 37,/*"土耳其文","TURKEA",*/
	SONG_JINPO = 38,/*景颇文*/

	// indian local language
	SONG_Garba = 39,
	SONG_Gujarati = 40,
	SONG_Malayalum = 41,
	SONG_Marathi = 42,
	SONG_Tamil = 43,
	SONG_Telugu = 44,
	SONG_Bengali = 45,
	SONG_Kannada = 46,
	SONG_Sinhala = 47,
	SONG_Konkani = 48,
	SONG_Urdu = 49,
	SONG_Punjabi = 50,

	SONG_Translate = 51,
	
} krk_song_language_t;

/*
* the filetype and subfiletype we need
*/
enum //filetype
{
	SONG_FILETYPE_MUS = 1,
	SONG_FILETYPE_KSC = 2,
	SONG_FILETYPE_MTV = 3,
	SONG_FILETYPE_MP3 = 4,
	SONG_FILETYPE_MOVIE = 5,
	SONG_FILETYPE_OKF = 6,
	SONG_FILETYPE_CDG = 128,
	SONG_FILETYPE_LYC = 129,
	SONG_FILETYPE_MUK = 255,
};

//subFileType
enum
{
	SONG_SUBFILETYPE_MIDI = 1,
	SONG_SUBFILETYPE_MIDIMP3 = 2,
	SONG_SUBFILETYPE_KSC = 3	
};

enum //subfiletype
{
	SONG_MEDIATYPE_MIDI = 1,
	SONG_MEDIATYPE_MIDI_MP3 = 2,
	SONG_MEDIATYPE_MP3 = 3,
	
	SONG_MEDIATYPE_ACC = 17,

	SONG_MEDIATYPE_OKF_MIDI = 129,
	SONG_MEDIATYPE_OKF_ACC = 145,

	SONG_MEDIATYPE_FILE_MP3 = 200,
	SONG_MEDIATYPE_FILE_AVI = 201,

	SONG_MEDIATYPE_MTV_MUS = 254,
};

typedef void (*fileDetectCallback_t)(int, void*);
typedef void (*fileCopyCallback_t)(int, void*, void*);

#define DET_MAX_FILE_NAME_LEN			128

/*
*	detect file info
*/
typedef struct 
{
	char 	fileName[DET_MAX_FILE_NAME_LEN];				/* full path of file name */
	int		dir;							/* 0: file, 1: directory */
} detectFileInfo_t;

/*
*	file detect parameters
*/
typedef struct 
{
	detectFileInfo_t*			fileList;					/* file info list */
	int								fileCount;
	fileDetectCallback_t	startCallback;		/* callback function folked when detecting started */
	fileDetectCallback_t	fileCallback;			/* callback function deliver the file info */
	fileDetectCallback_t	endCallback;		/* callback function folked when detecting ended */
	
} fileDetectPara_t;

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Function name  	: cut_utf8str_bylength
 * Arguments      	: str - input utf8 string, length - allowed length								
 * Return         	: true - string is cut, false - do nothing
 * Description    	: cut utf8 string by input length
 *					
*/
extern int cut_utf8str_bylength(char *str, int length);

/*
 * Function name  	: xle_to_mong
 * Arguments      	: xle_ucs - xle unicode
 *										ucslen - unicode string length
 * Return         	: output mongol unicode
 * Description    	: convert xle unicode string to mongol unicode string
 *					
*/
extern void xle_to_mong(unsigned short* xle_ucs, int ucslen);
/*
 * Function name  	: ArabicAlpha_to_UnicodeID
 * Arguments      	: instr - Arabic Unicode 
 *					  inlen - Arabic Unicode length 
 *					  outlen- need Alpha len Arabic Unicode - xle unicode
 *					  
 * Return         	: outstr -output unicode ID
 * Description    	: get Arabic unicode string to  unicode ID
 *					
*/
void ArabicAlpha_to_UnicodeID(unsigned short* instr,char* outstr,int inlen,int outlen);

/*
 * Function name  	: krk_ucs_to_utf8
 * Arguments      	: in_ucs - input unicode string
 *									ucslen - input uncode string length in multiword
 *									out_utf8 - utf8 string buffer
 *									utf8len - utf8 string buffer size in bytes
 * Return         	: output utf8 string length
 * Description    	: convert unicode string to utf8 string
 *					
*/
extern int krk_ucs_to_utf8(unsigned short* in_ucs, int ucslen, char* out_utf8, int utf8len);

/*
 * Function name  	: krk_utf8_to_ucs
 * Arguments      	: in_utf8 - input utf8 code string
 *									out_ucs - output unicode string
 *									len1 - utf8 string length in bytes
 *									len2 - input unicode buffer size in bytes
 * Return         	: 1
 * Description    	: convert utf8 string to unicode string
 *					
*/
extern int krk_utf8_to_ucs(char* in_utf8, unsigned short* out_ucs, int len1, int len2);

/*
 * Function name  	: krk_check_cjk_unicode
 * Arguments      	: str - input unicode char
 * Return         	: true - cjk code, false - not cjk code
 * Description    	: check if the unicode char is cjk
*/
extern int krk_check_cjk_unicode(unsigned short str);

/*
 * Function name  	: krk_get_unicode_str_font_language
 * Arguments      	: str - input unicode string
 * Return         	: language id of input string
 * Description    	: get font language id of input string
*/
extern int krk_get_unicode_str_font_language(unsigned short* str);

/*
 * Function name  	: krk_get_string_font_language
 * Arguments      	: cp - code page of input string
 *									str - input string
 * Return         	: language id of input string
 * Description    	: get font language id of input string
*/
extern int krk_get_string_font_language(int cp, char* str);

/*
 * Function name  	: krk_font_language_to_cp
 * Arguments      	: LanType : language id
 *									
 * Return         	: code page id
 * Description    	: get code page id by font language id
*/
extern int krk_font_language_to_cp(int LanType);

/*
 * Function name  	: krk_font_language_to_cp
 * Arguments      	: LanType : song language id
 *									
 * Return         	: code page id
 * Description    	: get code page id by song language id
*/
extern int krk_song_language_to_cp(int LanType);

/*
 * Function name  	: krk_endian_check
 * Arguments      	: none
 * Return         	: KRK_BIG_ENDIAN or KRK_SMALL_ENDIAN
 * Description    	: check the endian type of current platform
 *					
*/
extern int krk_endian_check(void);

/*
 * Function name  	: krk_checksuffix
 * Arguments      	: fileName - filename string
 *									suffix - suffix string
 * Return         	: 0-succ, -1 err
 * Description    	: check if the file name suffix match the input suffix
 *					
*/
extern int krk_checksuffix(const char *FileName, const char *Suffix);

/*
 * Function name  	: krk_strncpy_fillspace
 * Arguments      	: dest - destiny string
 *									src - source string
 *									n - number of characters
 * Return         	: copyied number
 * Description    	: copy "n" characters from source to destiny, if source length is less than 'n', then fill blank space
 *					
*/
extern int krk_strncpy_fillspace(char *dest, const unsigned char  *src, int n);

/*
* get the first directory name in path, "a/b/c/d/" --> "a"
*
* @param
*		fullpath: full path string
*		name: first directory name string
* @return - 0: fullpath is blank or not '/' ended, <>0, the name string length
*/
extern int krk_catch_dirname_in_path(const char *fullpath, char *name);

/*
* get the file name in path, "a/b/c/d/e.f" --> "e.f"
*
* @param
*		fullpath: full path string
*		name: first directory name string
* @return - 0: fullpath is blank or not '/' ended, <>0, the name string length
*/
extern int krk_catch_filename_in_path(const char *fullpath, char *name);
/*
* get the full directory name in path, "a/b/c/d" --> "a/b/c/"
*
* @param
*		fullpath: full path string
*		name: first directory name string
* @return  0: fullpath is blank or not '/' ended, >0, the name string length
*/
extern int krk_catch_path_in_fullname(const char *fullname, char *path);

/*
 * Function name  	: krk_convert_path_split
 * Arguments      	: fullname - path name string
 *									maxlen - fullname string maximum length
 *									std_split - standard split character
 * Return         	: none
 * Description    	: path split characters '\\' or '/' will all converted to input standard split character
 *					
*/
extern void krk_convert_path_split(char *fullname, int maxlen, char std_split);

/*
 * Function name  	: krk_utf8_strlen
 * Arguments      	: utf8str - input utf8 string
 * Return         	: utf8 string length in utf8 code
 * Description    	: get input utf8 string length
 *					
*/
extern int krk_utf8_strlen(unsigned char* utf8str);

/*
 * Function name  	: krk_ucs_length
 * Arguments      	: ucs - input unicode string
 * Return         	: string length in unicode
 * Description    	: get input unicode string length
 *					
*/
extern int krk_ucs_strlen(unsigned short* ucs);
/*
 * Function name  	: krk_ucs_strcmp
 * Arguments      	: ucss - source unicode string
 *									ucsd - dest unicode string
 * Return         	: 0 - equal, <>0 
 * Description    	: compare unicode string
 *					
*/
extern int krk_ucs_strcmp(unsigned short* ucss, unsigned short* ucsd);

extern void krk_uppercase_xle(char *str);

extern void krk_uppercase(char *str);
extern void krk_lowcase(char *str);
extern void krk_substr(char *str, char* substr, int maxlen);

/*
* convert string to long integer
* param - 
*				str : '123456789ABCDEF' etc.
*				base : 8/10/16 etc.
*/
extern unsigned int krk_strtol(char *str, int base);

/*
* copy string, byte n is NULL 
*/
extern char* krk_strncpy(char *dst, const char* src, int n);

/*
* like strstr, but ignore case
*/
extern int krk_stristr(const char *str, const char* substr);

/*
* convert string to long integer
* param - 
*				str : '123456789ABCDEF' etc.
*				base : 8/10/16 etc.
*/
extern char* krk_itoa_ext(int num,char *str,int radix,int maxlen);

/*
 * Function name  	: krk_atoi
 * Arguments      	: str - input string
 * Return         	: 0 - succ, <>0 errcode
 * Description    	: convert string to integer
 *					
*/
extern unsigned int krk_atoi(char* str);

/*
 * Function name  	: krk_atoi
 * Arguments      	: val - integer value
 *										str - input string
 *										radix - 10/16
 * Return         	: string addr
 * Description    	: convert integer to string
 *					
*/
extern char* krk_itoa(int val, char* str, int radix);

/*
* convert bcd code to long integer
* param - 
*				bcd : 0x123 etc.
*				sz : byte count.
*/
extern unsigned int krk_bcd_conv(unsigned char *bcd, int sz);

/*
* convert integer to bcd 
* param - 
*				bcd : 0x123 etc.
*				sz : byte count.
*/
extern void krk_int2bcd(int val, unsigned char *bcd, int sz);

extern void *krk_swap_byte(void *pmem,int num);

/*
*	function : compare two string, ignore case, compare length is set by input argument
*	arguments:
*	@dst : string 1
*	@src : string 2
*	@len : compare length in bytes
*	return : 
*		0 : dst = src, >0: dst > src, <0 : dst < src
*/
extern int stricmpn(const char *dst, const char *src, int len);

extern int krk_extract_str(char* str);

extern gdi_rect_t krk_rect_and_rect(gdi_rect_t *r1, gdi_rect_t *r2);

/*
 * Function name  	: krk_detect_files
 * Arguments      	: para - input file detection parameters, check the detail in fileDetectPara_t
 * Return         	: 0-succ, <>0 errcode
 * Description    	: detect file/directory exists or not by input file list, you can set the callback functions to do something in detecting
 *					
*/
extern int krk_detect_files(fileDetectPara_t* para);

/*
 * Function name  	: krk_fcopy
 * Arguments      	: dest - destiny file name
 *									src - source file name
 *									bufsz - file data buffer size , buffer will malloc in krk_fcopy
 *									proc - process callback function, you can get copy percentage and filename here
 * Return         	: 0-succ, <>0 error
 * Description    	: copy file, you can set the callback functions to do something in copying
 *					
*/
extern int krk_fcopy(const char* dest, const char* src, int bufsz, fileCopyCallback_t proc);

/*
 * Function name  	: krk_fcopyext
 * Arguments      	: dest - destiny file name
 *									src - source file name
 *									bufsz - file data buffer size , buffer will malloc in krk_fcopy
 *									proc - process callback function, you can get copy percentage and filename here
 *									flag - 0 - overwrite, 1 - append
 * Return         	: 0-succ, <>0 error
 * Description    	: copy file, you can set the callback functions to do something in copying
 *					
*/
extern int krk_fcopyext(const char* dest, const char* src, int bufsz, fileCopyCallback_t proc, int append);
extern int krk_fcopy_check(const char* dest, const char* src, int bufsz, fileCopyCallback_t proc,int checkfg);

/*
 * Function name  	: krk_fcmp
 * Arguments      	: dest - destiny file name
 *									src - source file name
 *									bufsz - file data buffer size , buffer will malloc in krk_fcopy
 * Return         	: 0-same, <>0 not same
 * Description    	: compare file
 *					
*/
extern int krk_fcmp(const char* dest, const char* src, int bufsz);

/*
 * Function name  	: krk_xremove
 * Arguments      	: srcdir - src file or folder to remove
 * Return         	: > 0 remove file count, < 0 , error
 * Description    	: remove file or directory
 *					
*/
extern int krk_xremove(const char *srcdir);

/*
 * Function name  	: krk_xremove_ext
 * Arguments      	: dirname - folder name
 *									extname - extend name
 * Return         	: > 0 remove file count, < 0 , error
 * Description    	: remove all file by extend name
 *					
*/
extern int krk_xremove_ext(const char *dirname,const char *extname);

/*
 * Function name  	: krk_xcopy
 * Arguments      	: dstdir - destiny file name
 *									srcdir - source file name
 *									bufsz - file data buffer size , buffer will malloc in krk_fcopy
 *									proc - process callback function, you can get copy percentage and filename here
 * Return         	: 0-succ, <>0 error
 * Description    	: copy file or directory, you can set the callback functions to do something in copying
 *					
*/
extern int krk_xcopy(const char *dstdir,const char *srcdir, int bufsz, fileCopyCallback_t proc);

/*
 * Function name  	: krk_xcopy_ext
 * Arguments      	: dstdir - destiny folder
 *									srcdir - source folder
 *									extname - extend name
 *									cpybufsz - copy file buffer size, fcopy parameter
 * Return         	: 0-succ, <>0 error
 * Description    	: copy files by extend name
 *					
*/
extern int krk_xcopy_ext(const char *dstdir,const char *srcdir,char *extname, int cpybufsz);
extern int krk_xcopy_check(char *dstdir,char *srcdir, int bufsz, fileCopyCallback_t proc,int checkfg);

/*
 * Function name  	: krk_file_num
 * Arguments      	: dirname - folder name
 *									extname - extend name
 * Return         	: file count
 * Description    	: get file count by extend file name in folder
 *					
*/
extern int krk_file_num(char *dirname,char *extname);


/*
 * Function name  	: krk_fexists
 * Return         	: true - exist, else false
 * Description    	: check the file exist
 *					
*/
extern int krk_fexist(const char *path);

/*
 * Function name  	: krk_fexists
 * Return         	: true - exist, else false
 * Description    	: check the dir exist
 *					
*/
extern int krk_direxist(const char *path);

/*
 * Function name  	: krk_GetSortStrByUcs
 * Arguments      	: ucs - unicode								
 * Return         	: sortString
 * Description    	: Get sortString by unicode
 *					
*/
extern unsigned short krk_GetSortStrByUcs (unsigned short usc);

extern void krk_convert_sortStr(char *des, char *sortStr);

extern void krk_vn_to_ucs(short *ucs_out, int ucslen, unsigned char *vn_in);
extern void krk_ucs_to_vn(unsigned char *vn_out, int vnlen, unsigned short *ucs_in);

#ifdef __cplusplus
}
#endif 

#endif

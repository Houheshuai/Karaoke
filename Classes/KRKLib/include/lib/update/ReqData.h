#ifndef _REQDATA_H_
#define _REQDATA_H_

#define REQ_FIELD_MAX				256
#define REQ_DATA_CAP				10000

#define REQ_CHARSET_UTF8			0
#define REQ_CHARSET_UNICODE			1
#define REQ_CHARSET_ORIGINAL			2

typedef enum						//请求数据源类型
{
	em_songlist = 0,
	em_mukfile,
	em_vdkfile,
}req_type_em;	

typedef enum						//请求字段类型
{
	em_byte = 0,
	em_short,
	em_int,
	em_string,
	em_auto,
}field_type_em;

typedef enum						//请求字段枚举
{
	em_songindex = 0,				//歌曲号				Order
	em_orderindex,					//点歌号				Order
	em_songname,					//歌曲名				SongName
	em_singername,					//歌手名				Singer
	em_lyricname,					//词作者				LyricWriter
	em_composername,				//曲作者				MusicWriter
	em_language,					//歌曲语言			LanType
	em_songnamealpha,				//歌曲名α			Alpha

	em_typenumber,					//类型号				""
	em_songtype,					//歌曲类型			""

	em_singersex,					//歌手性别			Sex
	em_singerarea,					//歌手区域			LanType
	em_singernamealpha,				//歌手名α			Alpha

	em_filetype,					//文件类型			FileType
	em_subfiletype,					//子文件类型			SubFileType
	em_sortstring,					//排序字符串			SortString

	em_fileid,						//文件ID				FileID
	em_songnameunicode,				//unicode 歌曲名		""
	
	em_songnamefirstword,			//歌曲首拼			FirstWord
	em_singernamefirstword,			//歌手首拼			FirstWord
	em_songnamefullword, 		//歌曲全拼			FullWord
	em_singernamefullword, 		//歌手全拼			FullWord

	em_zhizuohao,					//制作号				ZhiZuoHao
	em_firststroke,					//		FirstStroke
	em_backvideo,					//		BackVideo
	em_ordertimes,					//		OrderTimes
	em_words,						//		Words
	em_sortindex,					//		SortIndex
	
	em_singersortstring,			//		SortString	
	em_singerfield,					//		Field
	em_singerindex,
	em_singernameen,

	em_fonttype,					// fonttype
	em_songnameglyphoffset,					// SongNameGlyphOffset
	em_singersongtotal,

	em_default,
	em_Bhajanfg,
	em_Patrioticfg,
	em_Duetfg,
	em_Solofg,
	em_Sufifg,
	em_Romaticfg,
	em_Ghazalfg,
	em_Everfg,
	em_Birthdayfg,
	em_Classicalfg,
	em_Popularfg,
#if 1   //Persang db album function
	em_albumindex,
	em_albumname,
	em_albumnameen,
	em_albumsortstring,			//		SortString	
	em_albumfield,					//		Field
	em_albumnamefirstword,
	em_albumnamefullword,
#endif
	em_field_count,
}req_field_em;


typedef struct tag_req_field_t			req_field_t;
typedef struct tag_req_table_t			req_table_t;
typedef struct tag_table_field_t		table_field_t;
typedef int (ret_data_pop)(req_table_t *,int);
typedef int (ret_data_push)(req_table_t *);
typedef void (req_data_cb)(void *,int,int);
typedef	ret_data_pop					*rd_cleanup;
typedef	ret_data_pop					*rd_pop;
typedef	ret_data_push					*rd_push;
typedef req_data_cb						*req_cb;
typedef int (*singer_namechk_cb)(void* cache, const char* singername, int singerindex, int* songtotal);
typedef int (*singer_gettotal_cb)(void* cache, int singerindex);

struct tag_req_field_t
{
	int len[em_field_count];			//字段的长度
};

struct tag_table_field_t				//表字段
{	
	int field_len;						//字段的长度
	int field_offset;					//在请求结果中的偏移
	req_field_em em_field;				//字段的枚举
	field_type_em em_field_type;		//字段的类型
	char field_data[REQ_FIELD_MAX];		//字段的数据
};

struct tag_req_table_t					//请求表
{
	int recode_num;						//表中字段的个数
	int recode_size;					//表中记录的长度
	int charset;						//表中字段编码 0 - 普通 1 - unicode
	int cn_firstword;				// 只请求中文首拼
	table_field_t field[em_field_count];//字段数组
	void *ret_data;						//请求到的数据	
	rd_cleanup req_cleanup;
	rd_pop req_pop;
	rd_push req_push;
	void *usrdata;
	req_cb req_dcb;
};

#ifdef __cplusplus
extern "C" {
#endif
	/**
	*	释放请求表
	*/
	void req_table_deinit(req_table_t *prt);
	/**
	*	初始化请求表 如果prt为NULL则从堆中申请一块内存 返回初始化后的指针
	*	通过一个字段长度的数组初始化请求表，数组中长度为0的字段表示不请求该字段
	*	当字段类型为字符串时长度表示该字符串的长度
	*/
	req_table_t *req_table_init(req_table_t *prt,req_field_t *pfield);
	/**
	*	请求数据，返回请求的记录的个数
	*/
	int req_data(req_table_t *prt,req_type_em type,const char *dir_path,void *para);
	/**
	*	清除请求到的数据
	*/
	void req_data_cls(req_table_t *prt);
	/**
	*	设置要请求的字段，不过设置时会自动把请求到的数据清除
	*/
	void req_field_set(req_table_t *prt,req_field_em em_field,int len);
	/**
	*	将请求到的数据写到文件里
	*/
	int req_data_write(req_table_t *prt,const char *path);
	/**
	*	从文件里读出请求到的数据
	*/
	req_table_t *req_data_read(const char *path);
	/**
	*	将指定的请求表复制一份
	*/
	req_table_t *req_table_clone(req_table_t *prt);
	/**
	*	删除pdst中与psrc相同的记录 如果em_field字段的值相同则表示两个记录相同
	*/
	int req_merge_same(req_table_t *pdst,req_table_t *psrc,req_field_em em_field);
	/**
	*	删除prt中相同的记录 如果em_field字段的值相同则表示两个记录相同
	*/
	int req_delete_same(req_table_t *prt,req_field_em em_field);

	/**
	* merge same singer index
	*/
	void req_merge_singer_index(req_table_t *prt, int singerstartid, void* singerCache, singer_namechk_cb cb);

	void req_merge_singer_songtotal(req_table_t *prt, void* singerCache, singer_gettotal_cb cb);

	/**
	*	将表中的指定字段自加，字段必须是int类型的
	*   例如  INDEX      FIELD
	*			0      	 base
	*			1		base + 1
	*			2		base + 2
	*		   ...		base + ...
	*/
	int req_increase_set(req_table_t *prt,int base,req_field_em em_field);
	/**
	*	比较两个表中任意两条记录的key字段,如果相同则把这两条记录中的cpy字段从psrc复制到pdst中
	*/
	int req_table_cpy(req_table_t *pdst,req_table_t *psrc,req_field_em key,req_field_em cpy);
	/**
	*	把psrc中的记录添加到pdst中
	*/
	int req_table_add(req_table_t *pdst,req_table_t *psrc);
	/**
	*	设置数据源的编码方式 utf8 unicode gb2312
	*/
	void req_set_charset(req_table_t *prt,int src_charset);
#ifdef __cplusplus
}
#endif

/************************************************************************/
/* switch(em_field)
{
case em_songnumber:return em_int;
case em_songname:return;
case em_singername:return;
case em_lyricname:return;
case em_composername:return;
case em_language:return;
case em_songnamealpha:return;
case em_typenumber:return;
case em_songtype:return;
case em_singersex:return;
case em_singerarea:return;
case em_singernamealpha:return;
case em_filetype:return;
case em_subfiletype:return;
case em_sortstring:return;
case em_fileid:return;
case em_songnameunicode:return;
case em_songnamefirstword:return;
case em_singernamefirstword:return;
case em_zhizuohao:return;
case em_firststroke:return;
case em_backvideo:return;
case em_ordertimes:return;
case em_words:return;
case em_sortindex:return;
case em_singersortstring:return;
case em_singerfield:return;
}                                                                     */
/************************************************************************/


#endif

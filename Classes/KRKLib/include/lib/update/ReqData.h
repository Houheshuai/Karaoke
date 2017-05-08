#ifndef _REQDATA_H_
#define _REQDATA_H_

#define REQ_FIELD_MAX				256
#define REQ_DATA_CAP				10000

#define REQ_CHARSET_UTF8			0
#define REQ_CHARSET_UNICODE			1
#define REQ_CHARSET_ORIGINAL			2

typedef enum						//��������Դ����
{
	em_songlist = 0,
	em_mukfile,
	em_vdkfile,
}req_type_em;	

typedef enum						//�����ֶ�����
{
	em_byte = 0,
	em_short,
	em_int,
	em_string,
	em_auto,
}field_type_em;

typedef enum						//�����ֶ�ö��
{
	em_songindex = 0,				//������				Order
	em_orderindex,					//����				Order
	em_songname,					//������				SongName
	em_singername,					//������				Singer
	em_lyricname,					//������				LyricWriter
	em_composername,				//������				MusicWriter
	em_language,					//��������			LanType
	em_songnamealpha,				//��������			Alpha

	em_typenumber,					//���ͺ�				""
	em_songtype,					//��������			""

	em_singersex,					//�����Ա�			Sex
	em_singerarea,					//��������			LanType
	em_singernamealpha,				//��������			Alpha

	em_filetype,					//�ļ�����			FileType
	em_subfiletype,					//���ļ�����			SubFileType
	em_sortstring,					//�����ַ���			SortString

	em_fileid,						//�ļ�ID				FileID
	em_songnameunicode,				//unicode ������		""
	
	em_songnamefirstword,			//������ƴ			FirstWord
	em_singernamefirstword,			//������ƴ			FirstWord
	em_songnamefullword, 		//����ȫƴ			FullWord
	em_singernamefullword, 		//����ȫƴ			FullWord

	em_zhizuohao,					//������				ZhiZuoHao
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
	int len[em_field_count];			//�ֶεĳ���
};

struct tag_table_field_t				//���ֶ�
{	
	int field_len;						//�ֶεĳ���
	int field_offset;					//���������е�ƫ��
	req_field_em em_field;				//�ֶε�ö��
	field_type_em em_field_type;		//�ֶε�����
	char field_data[REQ_FIELD_MAX];		//�ֶε�����
};

struct tag_req_table_t					//�����
{
	int recode_num;						//�����ֶεĸ���
	int recode_size;					//���м�¼�ĳ���
	int charset;						//�����ֶα��� 0 - ��ͨ 1 - unicode
	int cn_firstword;				// ֻ����������ƴ
	table_field_t field[em_field_count];//�ֶ�����
	void *ret_data;						//���󵽵�����	
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
	*	�ͷ������
	*/
	void req_table_deinit(req_table_t *prt);
	/**
	*	��ʼ������� ���prtΪNULL��Ӷ�������һ���ڴ� ���س�ʼ�����ָ��
	*	ͨ��һ���ֶγ��ȵ������ʼ������������г���Ϊ0���ֶα�ʾ��������ֶ�
	*	���ֶ�����Ϊ�ַ���ʱ���ȱ�ʾ���ַ����ĳ���
	*/
	req_table_t *req_table_init(req_table_t *prt,req_field_t *pfield);
	/**
	*	�������ݣ���������ļ�¼�ĸ���
	*/
	int req_data(req_table_t *prt,req_type_em type,const char *dir_path,void *para);
	/**
	*	������󵽵�����
	*/
	void req_data_cls(req_table_t *prt);
	/**
	*	����Ҫ������ֶΣ���������ʱ���Զ������󵽵��������
	*/
	void req_field_set(req_table_t *prt,req_field_em em_field,int len);
	/**
	*	�����󵽵�����д���ļ���
	*/
	int req_data_write(req_table_t *prt,const char *path);
	/**
	*	���ļ���������󵽵�����
	*/
	req_table_t *req_data_read(const char *path);
	/**
	*	��ָ�����������һ��
	*/
	req_table_t *req_table_clone(req_table_t *prt);
	/**
	*	ɾ��pdst����psrc��ͬ�ļ�¼ ���em_field�ֶε�ֵ��ͬ���ʾ������¼��ͬ
	*/
	int req_merge_same(req_table_t *pdst,req_table_t *psrc,req_field_em em_field);
	/**
	*	ɾ��prt����ͬ�ļ�¼ ���em_field�ֶε�ֵ��ͬ���ʾ������¼��ͬ
	*/
	int req_delete_same(req_table_t *prt,req_field_em em_field);

	/**
	* merge same singer index
	*/
	void req_merge_singer_index(req_table_t *prt, int singerstartid, void* singerCache, singer_namechk_cb cb);

	void req_merge_singer_songtotal(req_table_t *prt, void* singerCache, singer_gettotal_cb cb);

	/**
	*	�����е�ָ���ֶ��Լӣ��ֶα�����int���͵�
	*   ����  INDEX      FIELD
	*			0      	 base
	*			1		base + 1
	*			2		base + 2
	*		   ...		base + ...
	*/
	int req_increase_set(req_table_t *prt,int base,req_field_em em_field);
	/**
	*	�Ƚ�������������������¼��key�ֶ�,�����ͬ�����������¼�е�cpy�ֶδ�psrc���Ƶ�pdst��
	*/
	int req_table_cpy(req_table_t *pdst,req_table_t *psrc,req_field_em key,req_field_em cpy);
	/**
	*	��psrc�еļ�¼��ӵ�pdst��
	*/
	int req_table_add(req_table_t *pdst,req_table_t *psrc);
	/**
	*	��������Դ�ı��뷽ʽ utf8 unicode gb2312
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

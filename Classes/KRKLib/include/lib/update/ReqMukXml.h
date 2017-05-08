#ifndef _REQMUKXML_H_
#define _REQMUKXML_H_

#define XML_FIELD_NAME_MAX		16
typedef struct tag_muk_xml_t muk_xml_t;
typedef struct tag_mark_xml_t mark_xml_t;
typedef struct tag_xml_field_t	xml_field_t;

struct tag_mark_xml_t
{
	mark_head_t head;
	char xml_tag[30];
};
struct tag_xml_field_t
{
	char have;						//0 - not req ;1 - req
	char area;						//0 - in song;1 - in singer;
	char name[XML_FIELD_NAME_MAX];	//Name
};
struct tag_muk_xml_t
{
	xml_field_t field[em_field_count];
	void *song;
	void *singer;
};

#ifdef __cplusplus
extern "C" {
#endif
	/**
	*	请求xml中的数据，成功返回 1 失败返回 0
	*/
	int mukxml_muk_get_data(req_table_t *prt,muk_t *pmuk);
#ifdef __cplusplus
}
#endif

#endif

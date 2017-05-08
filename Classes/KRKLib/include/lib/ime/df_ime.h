#ifndef _DF_IME_H_
#define _DF_IME_H_

#define IME_INPUT_MAX 64

typedef enum					//ģ��״̬
{
	ime_state_ready_em,			//׼��״̬
	ime_state_wait_em,			//�ȴ�״̬
	ime_state_timeout_em,		//ʱ�����״̬
	ime_state_end_em,			//����״̬
	ime_state_err_em			//����״̬
}ime_state_em;

typedef enum					//ģ���ʱ��״̬
{
	ime_state_timer_stop_em = 0,//��ʱ��ֹͣ
	ime_state_timer_run_em		//��ʱ������
}ime_state_timer_em;

typedef enum 					//�ص�����ö�� 
{	
	ime_cb_keystart_em = 0,		//������ʼ
	ime_cb_keychange_em,		//��������
	ime_cb_keyend_em,			//��������
	ime_cb_keyerr_em,			//��������
	ime_cb_func_bs_em,			//�˸���
	ime_cb_func_cls_em,			//��չ���
	ime_cb_func_change_lan, 		//�л�����
	ime_cb_total_em				//����ö������
}ime_callback_em;


typedef enum					//������
{
	IME_FUNC_KEY_EM,			//���ܼ�
	IME_MULTIVALUE_KEY_EM,		//��ֵ���ּ�
	IME_ONEVALUE_KEY_EM			//��ֵ���ּ�
}ime_key_type_em;	

typedef enum
{
	IME_LANGUAGE_NONE = -1,
	IME_LANGUAGE_EN = 0,
	IME_LANGUAGE_CN,
	IME_LANGUAGE_KR,
	IME_LANGUAGE_RU,
	IME_LANGUAGE_MONG,

	IME_LANGUAGE_CNT,
	
}ime_language_em;

typedef enum					//�߼���ֵ
{
	IME_KEY_NUM0_EM = 0,		//���ּ� 0
	IME_KEY_NUM1_EM,			//���ּ� 1
	IME_KEY_NUM2_EM,			//���ּ� 2
	IME_KEY_NUM3_EM,			//���ּ� 3
	IME_KEY_NUM4_EM,			//���ּ� 4
	IME_KEY_NUM5_EM,			//���ּ� 5
	IME_KEY_NUM6_EM,			//���ּ� 6
	IME_KEY_NUM7_EM,			//���ּ� 7
	IME_KEY_NUM8_EM,			//���ּ� 8
	IME_KEY_NUM9_EM,			//���ּ� 9
	IME_BACK_SPACE_EM,			//���ܼ� �˸�
	IME_CLEAR_EM,				//���ܼ� ���
	IME_KEY_TOTAL_EM,			//�߼�������
}ime_key_em;

typedef struct tagIme_t ime_t;
typedef struct tagKeyMap_t ime_keymap_t;

typedef int (ime_handle)(int,void *);
typedef ime_handle *ime_hdl;

typedef int (ime_method)(ime_t *,int);
typedef ime_method *ime_mtd;


typedef struct								//�������� ��ֵӳ��
{
	int real_key;
	ime_key_em logic_key;
}tagKeyMapItem_t;

struct tagKeyMap_t
{
	tagKeyMapItem_t item[IME_KEY_TOTAL_EM];
};

struct tagKeyMap_st;						//˽������ ��ֵӳ�� 
typedef struct tagKeyMap_st *key_map_pt;

struct tagIme_t
{
	int cur_key_value;
	int cur_real_key;
	int ime_state;

	unsigned char cacheinput[IME_INPUT_MAX];
	unsigned char cacheinput_utf8[IME_INPUT_MAX];
	unsigned int	cachesz;

	ime_language_em language;
	ime_state_timer_em time_state;
	unsigned int time_count;
	
	unsigned int time_out;
	void *usrdata;

	unsigned int input_max;
	
	ime_hdl *ime_cb;
	key_map_pt key_map;
	
	/*
	 * Method name		: time_update
	 * Arguments		: p_ime - ģ����� 
	 *					  time - ʱ���� ��λ ���� 
	 * Return 			: �ȴ�״̬��������ʱ�� ��λ ����
	 * Description		: ģ���ʱ��Դ
	*/
	ime_mtd time_update;
	
	/*
	 * Method name		: send_key
	 * Arguments		: p_ime - ģ����� 
	 *					  vkey - �ⲿ������ַ� 
	 * Return 			: ģ�鵱ǰ��״̬
	 * Description		: ģ�������Դ�����ⲿ������ʱ����
	*/
	ime_mtd send_key;
};

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************* 
** Function name  : ime_init
** Arguments      : time_out - ��ʱ��С ��λ ����
**                  data - �û�����
** Return         : ģ�����
** Date&Time      : 2012-11-21
** Description    : ģ���ʼ��
*********************************************************************************************/ 
ime_t *ime_init(unsigned int time_out,void *data);

/********************************************************************************************* 
** Function name  : ime_deinit
** Arguments      : p_ime - ģ�����
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : ģ��ע��
*********************************************************************************************/ 
void ime_deinit(ime_t *p_ime);

/********************************************************************************************* 
** Function name  : ime_set_keymap
** Arguments      : p_ime - ģ�����
**                  key_map - ����ӳ���ָ��
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : ���ð���ӳ���
*********************************************************************************************/ 
void ime_set_keymap(ime_t *p_ime,ime_keymap_t *key_map);

/********************************************************************************************* 
** Function name  : ime_set_handle
** Arguments      : p_ime - ģ�����
**                  handle_no - �ص��������  
**                  handle - �ص�������ڵ�ַ
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : ���ûص�����
*********************************************************************************************/ 
void ime_set_handle(ime_t *p_ime,ime_callback_em handle_no,ime_hdl handle);

/********************************************************************************************* 
** Function name  : ime_set_usrdata
** Arguments      : p_ime - 
**                  usrdata - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : �����û�����
*********************************************************************************************/ 
void ime_set_usrdata(ime_t *p_ime,void *usrdata);

/********************************************************************************************* 
** Function name  : ime_set_max_input
** Arguments      : p_ime - 
**                  max_input - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : ����������볤��
*********************************************************************************************/ 
void ime_set_max_input(ime_t *p_ime, int max_input);

/********************************************************************************************* 
** Function name  : ime_change_language
** Arguments      : p_ime - 
**                  usrdata - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : �������뷨����
*********************************************************************************************/ 
void ime_change_language(ime_t *p_ime, ime_language_em lan);

/********************************************************************************************* 
** Function name  : ime_get_input
** Arguments      : p_ime - 
** Return         : �����ַ��� 
** Date&Time      : 2012-11-21
** Description    : ��ȡ�����ַ�
*********************************************************************************************/ 
unsigned char* ime_get_input(ime_t *p_ime);

unsigned char* ime_get_input_utf8(ime_t *p_ime);

/********************************************************************************************* 
** Function name  : ime_set_input
** Arguments      : p_ime - 
** Return         : copy len
** Date&Time      : 2012-11-21
** Description    : ��ȡ�����ַ�
*********************************************************************************************/ 
int ime_set_input(ime_t *p_ime, unsigned char* in, int len);

/********************************************************************************************* 
** Function name  : ime_reset
** Arguments      : p_ime - 
** Return         : 
** Date&Time      : 2012-11-21
** Description    : ��������ַ��� 
*********************************************************************************************/ 
void ime_reset(ime_t *p_ime);

#ifdef __cplusplus
}
#endif

#endif


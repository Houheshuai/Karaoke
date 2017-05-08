#ifndef _DF_IME_H_
#define _DF_IME_H_

#define IME_INPUT_MAX 64

typedef enum					//模块状态
{
	ime_state_ready_em,			//准备状态
	ime_state_wait_em,			//等待状态
	ime_state_timeout_em,		//时间溢出状态
	ime_state_end_em,			//结束状态
	ime_state_err_em			//错误状态
}ime_state_em;

typedef enum					//模块计时器状态
{
	ime_state_timer_stop_em = 0,//计时器停止
	ime_state_timer_run_em		//计时器运行
}ime_state_timer_em;

typedef enum 					//回调函数枚举 
{	
	ime_cb_keystart_em = 0,		//按键开始
	ime_cb_keychange_em,		//按键更改
	ime_cb_keyend_em,			//按键结束
	ime_cb_keyerr_em,			//按键错误
	ime_cb_func_bs_em,			//退格功能
	ime_cb_func_cls_em,			//清空功能
	ime_cb_func_change_lan, 		//切换语种
	ime_cb_total_em				//函数枚举总数
}ime_callback_em;


typedef enum					//键类型
{
	IME_FUNC_KEY_EM,			//功能键
	IME_MULTIVALUE_KEY_EM,		//多值数字键
	IME_ONEVALUE_KEY_EM			//单值数字键
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

typedef enum					//逻辑键值
{
	IME_KEY_NUM0_EM = 0,		//数字键 0
	IME_KEY_NUM1_EM,			//数字键 1
	IME_KEY_NUM2_EM,			//数字键 2
	IME_KEY_NUM3_EM,			//数字键 3
	IME_KEY_NUM4_EM,			//数字键 4
	IME_KEY_NUM5_EM,			//数字键 5
	IME_KEY_NUM6_EM,			//数字键 6
	IME_KEY_NUM7_EM,			//数字键 7
	IME_KEY_NUM8_EM,			//数字键 8
	IME_KEY_NUM9_EM,			//数字键 9
	IME_BACK_SPACE_EM,			//功能键 退格
	IME_CLEAR_EM,				//功能键 清空
	IME_KEY_TOTAL_EM,			//逻辑键总数
}ime_key_em;

typedef struct tagIme_t ime_t;
typedef struct tagKeyMap_t ime_keymap_t;

typedef int (ime_handle)(int,void *);
typedef ime_handle *ime_hdl;

typedef int (ime_method)(ime_t *,int);
typedef ime_method *ime_mtd;


typedef struct								//公共类型 键值映射
{
	int real_key;
	ime_key_em logic_key;
}tagKeyMapItem_t;

struct tagKeyMap_t
{
	tagKeyMapItem_t item[IME_KEY_TOTAL_EM];
};

struct tagKeyMap_st;						//私有类型 键值映射 
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
	 * Arguments		: p_ime - 模块对象 
	 *					  time - 时间间隔 单位 毫秒 
	 * Return 			: 等待状态所经过的时间 单位 毫秒
	 * Description		: 模块的时钟源
	*/
	ime_mtd time_update;
	
	/*
	 * Method name		: send_key
	 * Arguments		: p_ime - 模块对象 
	 *					  vkey - 外部输入的字符 
	 * Return 			: 模块当前的状态
	 * Description		: 模块的输入源，当外部有输入时调用
	*/
	ime_mtd send_key;
};

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************* 
** Function name  : ime_init
** Arguments      : time_out - 超时大小 单位 毫秒
**                  data - 用户数据
** Return         : 模块对象
** Date&Time      : 2012-11-21
** Description    : 模块初始化
*********************************************************************************************/ 
ime_t *ime_init(unsigned int time_out,void *data);

/********************************************************************************************* 
** Function name  : ime_deinit
** Arguments      : p_ime - 模块对象
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 模块注销
*********************************************************************************************/ 
void ime_deinit(ime_t *p_ime);

/********************************************************************************************* 
** Function name  : ime_set_keymap
** Arguments      : p_ime - 模块对象
**                  key_map - 按键映射表指针
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 设置按键映射表
*********************************************************************************************/ 
void ime_set_keymap(ime_t *p_ime,ime_keymap_t *key_map);

/********************************************************************************************* 
** Function name  : ime_set_handle
** Arguments      : p_ime - 模块对象
**                  handle_no - 回调函数编号  
**                  handle - 回调函数入口地址
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 设置回调函数
*********************************************************************************************/ 
void ime_set_handle(ime_t *p_ime,ime_callback_em handle_no,ime_hdl handle);

/********************************************************************************************* 
** Function name  : ime_set_usrdata
** Arguments      : p_ime - 
**                  usrdata - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 设置用户数据
*********************************************************************************************/ 
void ime_set_usrdata(ime_t *p_ime,void *usrdata);

/********************************************************************************************* 
** Function name  : ime_set_max_input
** Arguments      : p_ime - 
**                  max_input - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 设置最大输入长度
*********************************************************************************************/ 
void ime_set_max_input(ime_t *p_ime, int max_input);

/********************************************************************************************* 
** Function name  : ime_change_language
** Arguments      : p_ime - 
**                  usrdata - 
** Return         : void 
** Date&Time      : 2012-11-21
** Description    : 设置输入法语言
*********************************************************************************************/ 
void ime_change_language(ime_t *p_ime, ime_language_em lan);

/********************************************************************************************* 
** Function name  : ime_get_input
** Arguments      : p_ime - 
** Return         : 输入字符串 
** Date&Time      : 2012-11-21
** Description    : 获取输入字符
*********************************************************************************************/ 
unsigned char* ime_get_input(ime_t *p_ime);

unsigned char* ime_get_input_utf8(ime_t *p_ime);

/********************************************************************************************* 
** Function name  : ime_set_input
** Arguments      : p_ime - 
** Return         : copy len
** Date&Time      : 2012-11-21
** Description    : 获取输入字符
*********************************************************************************************/ 
int ime_set_input(ime_t *p_ime, unsigned char* in, int len);

/********************************************************************************************* 
** Function name  : ime_reset
** Arguments      : p_ime - 
** Return         : 
** Date&Time      : 2012-11-21
** Description    : 清除输入字符串 
*********************************************************************************************/ 
void ime_reset(ime_t *p_ime);

#ifdef __cplusplus
}
#endif

#endif


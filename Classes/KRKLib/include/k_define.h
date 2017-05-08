/*
** Copyright (C) 2011 Multak,Inc. All rights reserved								
**
** Filename : k_define.h
** Revision : 1.01											
**																	
** Description: common marco and api for normally use
** 
**************************************************************
** 
** History
**
** 1.00 
**       modified by yucx
** 1.01
**       modified by miaozy
** 1.02
**       modified by ...
**
*/

#ifndef _K_DEFINE_H_
#define _K_DEFINE_H_

#define KRK_LIB_VERSION			"1.73"

/* c_class flag */
#define _k_public					/* public attribute or method */
#define _k_private				/* private attribute or method */
#define _k_protect				/* protect attribute or method */

#ifdef __cplusplus
#define K_EXPORT	extern "C"
#else
#define K_EXPORT	extern
#endif

#define KRK_FRAME_RATE			30

/* combine strings in precompile */
#define krk_cat2(i,j)       i##j
#define krk_cat3(i,j,k)     i##j##k

/* min&max */
#define krk_max2(a,b)	((a)>(b)?(a):(b))
#define krk_max3(a,b,c)	krk_max2(krk_max2(a,b),c)
#define krk_min2(a,b)	((a)<(b)?(a):(b))
#define krk_min3(a,b,c)	krk_min2(krk_min2(a,b),c)

/* word&dword swap */
#define krk_swap(a)	( ((a) << 4 & 0xf0) | ((a) >> 4 & 0x0f))
#define krk_swap2(a)	( ((((unsigned short)(a))&0xff)<<8) | ((((unsigned short)(a))&0xff00)>>8) )
#define krk_swap4(a)	( ((((unsigned long)(a))&0xff)<<24) | ((((unsigned long)(a))&0xff00)<<8) | \
			  				((((unsigned long)(a))&0xff0000)>>8) | ((((unsigned long)(a))&0xff000000)>>24) )
#define krk_swap2b4b(a)	( ((((unsigned long)(a))&0xff000000)>>8) | ((((unsigned long)(a))&0xff0000)<<8) | \
						  ((((unsigned long)(a))&0xff)<<8) | ((((unsigned long)(a))&0xff00)>>8) )

#define krk_exchange(p, q)	 do { \
								 unsigned char tmp_xxxx;\
								 tmp_xxxx = *(p);\
								 *(p) = *(q);\
								 *(q) = tmp_xxxx;\
							} while (0);

#define krk_trunk_val(min, max, val)	val = ((val)<(min))? (min) : (((val) > (max))? (max) : (val))

/* usefull macro for calc buffer pointer in cycle buffer */
#define krk_buf_distance(front_ptr, back_ptr, val, buf_size) do { \
    (val) = (front_ptr) - (back_ptr); \
    if ((val) < 0) (val) += (buf_size); \
} while (0)

#define krk_buf_inc_ptr(ptr, ndword, buf_end, buf_size) do {\
    (ptr) += (ndword); \
    if ((ptr) >= (buf_end)) (ptr) -= (buf_size); \
} while (0)

#define krk_buf_dec_ptr(ptr, ndword, buf_start, buf_size) do {\
    (ptr) -= (ndword); \
    if ((ptr) < (buf_start)) (ptr) += (buf_size); \
} while (0)

/* bytes stream to integer */
#define K_GETLONG_LSB(addr) ((((unsigned char *)(addr))[3]<<24)+(((unsigned char *)(addr))[2]<<16)+(((unsigned char *)(addr))[1]<<8)+(((unsigned char *)(addr))[0]<<0))
#define K_GETLONG_MSB(addr) ((((unsigned char *)(addr))[0]<<24)+(((unsigned char *)(addr))[1]<<16)+(((unsigned char *)(addr))[2]<<8)+(((unsigned char *)(addr))[3]<<0))
#define K_GETSHORT_LSB(addr) ((((unsigned char *)(addr))[1]<<8)+(((unsigned char *)(addr))[0]<<0))
#define K_GETSHORT_MSB(addr) ((((unsigned char *)(addr))[0]<<8)+(((unsigned char *)(addr))[1]<<0))

#define K_SETLONG_LSB(val, addr) {((unsigned char *)(addr))[0]=((val)&0xff); ((unsigned char *)(addr))[1]=((val)>>8)&0xff; ((unsigned char *)(addr))[2]=((val)>>16)&0xff; ((unsigned char *)(addr))[3]=((val)>>24)&0xff;}
#define K_SETLONG_MSB(val, addr) {((unsigned char *)(addr))[3]=((val)&0xff); ((unsigned char *)(addr))[2]=((val)>>8)&0xff; ((unsigned char *)(addr))[1]=((val)>>16)&0xff; ((unsigned char *)(addr))[0]=((val)>>24)&0xff;}
#define K_SETSHORT_LSB(val, addr) {((unsigned char *)(addr))[0]=((val)&0xff); ((unsigned char *)(addr))[1]=((val)>>8)&0xff;}
#define K_SETSHORT_MSB(val, addr) {((unsigned char *)(addr))[1]=((val)&0xff); ((unsigned char *)(addr))[0]=((val)>>8)&0xff;}

#define K_BCD2INT_MSB(pBCD) 	((unsigned)(*(pBCD) & 0xf)*10000+(unsigned)(*((pBCD)+1)>>4)*1000+(unsigned)(*((pBCD)+1) & 0xf)*100+(*((pBCD)+2)>>4)*10+(*((pBCD)+2)&0xf))
#define K_BCD2INT_LSB(pBCD)		((unsigned)(*(pBCD) >>4)*10+(unsigned)(*(pBCD) & 0xf)+(unsigned)(*((pBCD)+1)>>4)*1000+(unsigned)(*((pBCD)+1) & 0xf)*100+(unsigned)(*((pBCD)+2)&0xf)*10000)

#define KRK_BIG_ENDIAN		0
#define KRK_SMALL_ENDIAN 	1

#define K_SHORT_ENDIANCONVERT(arc_en, data_en, data) ((arc_en == KRK_BIG_ENDIAN) && (data_en == KRK_SMALL_ENDIAN))? K_GETSHORT_MSB(&(data)) : (((arc_en == KRK_SMALL_ENDIAN) && (data_en == KRK_BIG_ENDIAN))? K_GETSHORT_LSB(&(data)) : (data))
#define K_LONG_ENDIANCONVERT(arc_en, data_en, data) ((arc_en == KRK_BIG_ENDIAN) && (data_en == KRK_SMALL_ENDIAN))? K_GETLONG_MSB(&(data)) : (((arc_en == KRK_SMALL_ENDIAN) && (data_en == KRK_BIG_ENDIAN))? K_GETLONG_LSB(&(data)) : (data))

#define KRK_RET_SUCC 				0
#define KRK_RET_ERR					-1
#define KRK_ERR_MALLOC				-2
#define KRK_ERR_PLAYFAIL			-3
#define KRK_ERR_MSG_TO_OWNER		-4
#define KRK_ERR_CTRL_NOT_VISABLE	-5
#define KRK_ERR_SCORE_ERR		-6
#define KRK_ERR_UNSUPPORT		-7
#define KRK_ERR_NOTFOUND		-8
#define KRK_ERR_LISTFULL		-9
#define KRK_ERR_MSG_KILLED		-10
#define KRK_ERR_FAVORATE_ADDED		-11
#define KRK_ERR_RECORD_CURSONG_FULL		-12
#define KRK_ERR_MSG_BYPASS			-13
#define KRK_ERR_NO_FREE_SPACE	-14
#define KRK_ERR_OPENFILE			-15

#endif

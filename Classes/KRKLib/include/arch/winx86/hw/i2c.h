#ifndef _MELIS_I2C_H_
#define _MELIS_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

int krk_i2c_req(int clk, int i2c_no);
int krk_i2c_rel(int hdle);
int krk_i2c_write_reg(int hdle, int addr, int offset, unsigned char* data, int datalen);
int krk_i2c_read_reg(int hdle, int addr, int offset, unsigned char *data, int datalen);
int krk_i2c_write_no_reg(int hdle, int addr, unsigned char* data, int datalen);
int krk_i2c_read_no_reg(int hdle, int addr, unsigned char* data, int datalen);

#ifdef __cplusplus
}
#endif

#endif


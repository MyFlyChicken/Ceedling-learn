#ifndef __bsp_i2c_H_ //shift+U转换为大写
#define __bsp_i2c_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int bsp_i2c_init(void);
int bsp_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);



#ifdef __cplusplus
}
#endif


#endif

#ifndef __sensor_H_ //shift+U转换为大写
#define __sensor_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int sensor_init(void);
int sensor_read_data(uint8_t address, uint8_t reg_addr, uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif


#endif

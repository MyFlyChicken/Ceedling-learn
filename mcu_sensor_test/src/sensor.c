#include "sensor.h"
#include "bsp_i2c.h"

int sensor_init(void)
{
    /* 传感器初始化代码 */    
    return bsp_i2c_init(); /* 成功 */
}

int sensor_read_data(uint8_t address, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return bsp_i2c_read(address, reg_addr, data, len);
}


#ifdef TEST

#include "unity.h"

/*!< 使用Cmock模拟外设，需要调用mock开头的头文件 */
#include "mock_bsp_i2c.h"
#include "sensor.h"
#include <stdio.h>
void setUp(void) { /*!< 测试环境初始化 */
  printf(""
         "Test Start...\n");
}

void tearDown(void) { /*!< 测试环境去初始化 */
  printf("Test End...\n");
}

void test_sensor_NeedToImplement(void) {

  int ret = 0;
  uint8_t value[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  uint8_t read_buffer[10] = {0};

  printf("__function__=%s, __LINE__=%d\n", __FUNCTION__, __LINE__);

  // bsp_i2c_read_ExpectWithArrayAndReturn(0x50, 0x01, value, 10, 0);
  bsp_i2c_read_ExpectAndReturn(0x50, 0x01, read_buffer, 10, 0);
  ret = sensor_read_data(0x50, 0x01, read_buffer, 10);
  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(read_buffer, read_buffer, 10);
}

void test_sensor_init_NeedToImplement(void) {
  int ret = 0;

  printf("__function__=%s, __LINE__=%d\n", __FUNCTION__, __LINE__);

  bsp_i2c_init_ExpectAndReturn(0);
  ret = sensor_init();
  TEST_ASSERT_EQUAL(0, ret);
}

#endif // TEST

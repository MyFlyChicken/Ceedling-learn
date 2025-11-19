
#ifdef TEST

#include "unity.h"

/*!< 使用Cmock模拟外设，需要调用mock开头的头文件 */
#include "mock_bsp_i2c.h"
#include "sensor.h"
#include <stdio.h>
void setUp(void) { /*!< 测试环境初始化 */
}

void tearDown(void) { /*!< 测试环境去初始化 */
}

void test_sensor_init(void) {
  int ret = 0;

  bsp_i2c_init_ExpectAndReturn(0);
  ret = sensor_init();
  TEST_ASSERT_EQUAL(0, ret);
}

void test_sensor_read_data_ret(void) {
  int ret = 0;
  uint8_t read_buffer[5] = {0};

  bsp_i2c_read_ExpectAndReturn(0x60, 0x02, read_buffer, 5, 0);
  ret = sensor_read_data(0x60, 0x02, read_buffer, 5);
  TEST_ASSERT_EQUAL(0, ret);
}

/**
 * @brief 测试读取内容是否符合预期
 *
 * @details 步骤1：编辑yml，使能cmock插件array和return_thru_ptr
 *          步骤2：设置bsp_i2c_read被调用时，返回值为0
 *          步骤2：设置bsp_i2c_read被调用时，将expected_buffer的数据赋值给实参data指向的内存
 */
void test_sensor_read_data_content(void) {
  int ret = 0;
  uint8_t read_buffer[5] = {0};
  uint8_t expected_buffer[5] = {10, 20, 30, 40, 50};

  // 设置bsp_i2c_read被调用时，返回值为0
  bsp_i2c_read_ExpectAndReturn(0x60, 0x02, read_buffer, 5, 0);
  // 设置bsp_i2c_read被调用时，将expected_buffer的数据赋值给实参data指向的内存
  bsp_i2c_read_ReturnArrayThruPtr_data(expected_buffer, 5);

  ret = sensor_read_data(0x60, 0x02, read_buffer, 5);
  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer, read_buffer, 5);
}

#endif // TEST

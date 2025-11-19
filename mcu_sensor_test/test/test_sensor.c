
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

  /* 连续设置返回值，每次调用sensor_init时，根据设置顺序返回 */
  /* 如果调用次数少于设置次数，那么该测试项校验不过 */
  bsp_i2c_init_ExpectAndReturn(0);
  bsp_i2c_init_ExpectAndReturn(1);
  /* 返回0 */
  ret = sensor_init();
  TEST_ASSERT_EQUAL(0, ret);
  /* 返回1 */
  ret = sensor_init();
  TEST_ASSERT_EQUAL(1, ret);
}

void test_sensor_init_ignore(void) {
  int ret = 0;

  /* 如果调用次数大于设置次数，那么bsp_i2c_init会返回最后一次设置的值1 */
  /* 如果调用次数少于设置次数，也不会报错 */
  bsp_i2c_init_IgnoreAndReturn(0);
  bsp_i2c_init_IgnoreAndReturn(1);
  ret = sensor_init();
  TEST_ASSERT_EQUAL(0, ret);
  ret = sensor_init();
  TEST_ASSERT_EQUAL(1, ret);
  ret = sensor_init();
  TEST_ASSERT_EQUAL(1, ret);
}

void test_sensor_read_data_ret(void) {
  int ret = 0;
  uint8_t read_buffer[5] = {0};

  /* 只关心返回值 */
  /* 如果调用次数少于设置次数，那么该测试项校验不过 */
  bsp_i2c_read_ExpectWithArrayAndReturn(
      0x60, 0x02, read_buffer, sizeof(read_buffer), sizeof(read_buffer), 0);
  bsp_i2c_read_ExpectWithArrayAndReturn(
      0x60, 0x02, read_buffer, sizeof(read_buffer), sizeof(read_buffer), 1);
  /* 返回0 */
  ret = sensor_read_data(0x60, 0x02, read_buffer, 5);
  TEST_ASSERT_EQUAL(0, ret);
  /* 返回1 */
  ret = sensor_read_data(0x60, 0x02, read_buffer, 5);
  TEST_ASSERT_EQUAL(1, ret);
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
  uint8_t expected_buffer1[5] = {10, 20, 30, 40, 50};
  uint8_t expected_buffer2[5] = {60, 70, 80, 90, 100};

  /* 第一组 */
  /* 必须先调用Expect函数，这个函数内部会申请内存并保存期望值，然后再调用ReturnArrayThruPtr函数，如果连续两个
  ReturnArrayThruPtr函数，会把第一次ReturnArrayThruPtr的设置覆盖*/
  // 设置bsp_i2c_read被调用时，返回值为0
  bsp_i2c_read_ExpectAndReturn(0x60, 0x01, read_buffer, 5, 0);
  // 设置bsp_i2c_read被调用时，将expected_buffer的数据赋值给实参data指向的内存
  bsp_i2c_read_ReturnArrayThruPtr_data(expected_buffer1, 5);

  /* 第二组 */
  bsp_i2c_read_ExpectAndReturn(0x60, 0x02, read_buffer, 5, 0);
  bsp_i2c_read_ReturnArrayThruPtr_data(expected_buffer2, 5);

  /* 第一组测试结果 */
  ret = sensor_read_data(0x60, 0x01, read_buffer, 5);
  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer1, read_buffer, 5);

  /* 第二组测试结果 */
  ret = sensor_read_data(0x60, 0x02, read_buffer, 5);
  TEST_ASSERT_EQUAL(0, ret);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_buffer2, read_buffer, 5);
}

#endif // TEST

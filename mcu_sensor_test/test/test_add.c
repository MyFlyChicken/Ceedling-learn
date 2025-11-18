
#ifdef TEST

#include "unity.h"

#include "add.h"

void setUp(void) { /*!< 测试环境初始化 */
}

void tearDown(void) { /*!< 测试环境去初始化 */
}

void test_add_NeedToImplement(void) {

  int result = add(2, 3);
  TEST_ASSERT_EQUAL(5, result);
}

#endif // TEST

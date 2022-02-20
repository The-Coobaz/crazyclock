#include <gtest/gtest.h>

#include "hello.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect for external function.
  EXPECT_EQ(test(), 0);
}

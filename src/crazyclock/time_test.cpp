#include <gtest/gtest.h>

#include "time.h"

TEST(TimeTest, SimpleAssertions) {

  LocalTime actual = fromEpochMillis(1234567);

  EXPECT_EQ(actual.hour, 12);
  EXPECT_EQ(actual.minute, 34);
  EXPECT_EQ(actual.second, 56);
}

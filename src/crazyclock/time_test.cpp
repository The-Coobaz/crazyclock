#include <gtest/gtest.h>

#include "time.h"

TEST(TimeTest, SomeDateTime) {
  // https://www.epochconverter.com/
  LocalTime actual = fromEpochMillis(1645390198000);

  EXPECT_EQ(actual.hour, 20);
  EXPECT_EQ(actual.minute, 49);
  EXPECT_EQ(actual.second, 58);
}

TEST(TimeTest, ShortAfterMidnight) {
  LocalTime actual = fromEpochMillis(1640995262000);

  EXPECT_EQ(actual.hour, 0);
  EXPECT_EQ(actual.minute, 1);
  EXPECT_EQ(actual.second, 2);
}

TEST(TimeTest, ZeroPoint) {

  LocalTime actual = fromEpochMillis(0);

  EXPECT_EQ(actual.hour, 0);
  EXPECT_EQ(actual.minute, 0);
  EXPECT_EQ(actual.second, 0);
}

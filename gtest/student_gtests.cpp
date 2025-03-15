#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(IsAdjacentTest, Equal) {
  EXPECT_TRUE(is_adjacent("apple", "apple"));
}

TEST(IsAdjacentTest, OneLetterDifference) {
    EXPECT_TRUE(is_adjacent("apple", "appla"));
}

TEST(IsAdjacentTest, OneLetterInsertion) {
    EXPECT_TRUE(is_adjacent("apple", "bapple"));
}

TEST(IsAdjacentTest, OneLetterDeletion) {
    EXPECT_TRUE(is_adjacent("apple", "appl"));
}
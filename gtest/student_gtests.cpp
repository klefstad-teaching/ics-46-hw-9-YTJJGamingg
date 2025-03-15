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

TEST(EditDistanceWithinTest, SameWords) {
    EXPECT_TRUE(edit_distance_within("apple", "apple", 1));
}

TEST(EditDistanceWithinTest, OneLetterInsertion) {
    EXPECT_TRUE(edit_distance_within("apple", "bapple", 1));
}

TEST(EditDistanceWithinTest, OneLetterDeletion) {
    EXPECT_TRUE(edit_distance_within("apple", "appl", 1));
}

TEST(EditDistanceWithinTest, OneLetterReplacement) {
    EXPECT_TRUE(edit_distance_within("apple", "appla", 1));
}

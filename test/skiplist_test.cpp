#include <gtest/gtest.h>
#include "skiplist.h"

using namespace skiplist;

// Demonstrate some basic assertions.
TEST(SKIPLIST, InsertTest1) {
  KeyComparator<int> cmp{};
  SkipList<int, KeyComparator<int>> sl{cmp};

  for (int i = 0; i < 10; i ++) {
    EXPECT_TRUE(sl.Insert(i));
  }

  sl.PrintSkipList();

  for (int i = 0; i < 10; i ++) {
    SkipList<int, KeyComparator<int>>::SkipListNode node;
    EXPECT_TRUE(sl.Find(i, &node));
    EXPECT_EQ(i, node.GetKey());
  }
}

// Demonstrate some basic assertions.
TEST(SKIPLIST, DeleteTest1) {
  KeyComparator<int> cmp{};
  SkipList<int, KeyComparator<int>> sl{cmp};

  for (int i = 0; i < 10; i ++) {
    EXPECT_TRUE(sl.Insert(i));
  }

  sl.PrintSkipList();

  for (int i = 0; i < 10; i ++) {
    SkipList<int, KeyComparator<int>>::SkipListNode node;
    EXPECT_TRUE(sl.Find(i, &node));
    EXPECT_EQ(i, node.GetKey());
  }

  // delete some elements
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      sl.Delete(i);
    }
  }
  sl.PrintSkipList();

  // make sure the existing elements are correct
  for (int i = 0; i < 10; i++) {
    SkipList<int, KeyComparator<int>>::SkipListNode node;
    if (i % 2 != 0) {
      EXPECT_TRUE(sl.Find(i, &node));
      EXPECT_EQ(i, node.GetKey());
    } else {
      EXPECT_FALSE(sl.Find(i, &node));
    }
  }
}

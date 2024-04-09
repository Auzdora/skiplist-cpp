#include "skiplist.h"

namespace skiplist {

/*****************************************************
              SkipList node abstraction
******************************************************/
template <typename Key, class Comparator>
SkipList<Key, Comparator>::SkipListNode::SkipListNode(Key key) : key_(key) {
  next_.resize(1);
}

template <typename Key, class Comparator>
SkipList<Key, Comparator>::SkipListNode::SkipListNode(Key key, int level) : key_(key) {
  next_.resize(level);
}

template <typename Key, class Comparator>
auto SkipList<Key, Comparator>::SkipListNode::GetNext(int n) -> SkipListNode * {
  return next_[n];
}

template <typename Key, class Comparator>
void SkipList<Key, Comparator>::SkipListNode::SetNext(int n, SkipListNode *next){
  next_[n] = next;
}

/*****************************************************
            SkipList method implementation
******************************************************/
template <typename Key, class Comparator>
SkipList<Key, Comparator>::SkipList(Comparator cmp) : cmp_(cmp) {}

template <typename Key, class Comparator>
auto SkipList<Key, Comparator>::Find(const Key &key, SkipListNode *node) -> bool {
  SkipListNode *cur_node = &head_;
  for (int i = max_height_ - 1; i >=0; i--) {
    while (cur_node->GetNext(i)) {
      if (cur_node->GetNext(i)->GetKey() == key) {
        *node = *cur_node->GetNext(i);
        return true;
      } else if (cur_node->GetNext(i)->GetKey() < key) {
        cur_node = cur_node->GetNext(i);
      } else {
        break;
      }
    }
  }
  return false;
}

template <typename Key, class Comparator>
auto SkipList<Key, Comparator>::Insert(const Key &key) -> bool {
  std::vector<SkipListNode *> prev(MaxHeight);
  if (!FindPrevNodes(key, prev)) {
    return false;
  }

  int rand_height = RandomHeight();

  if (rand_height > max_height_) {
    head_.Resize(rand_height);
    for (int i = max_height_; i < rand_height; i++) {
      prev[i] = &head_;
    }
    max_height_ = rand_height;
  }

  SkipListNode *insert_node = new SkipListNode(key, rand_height);
  for (int i = rand_height - 1; i >=0; i--) {
    insert_node->SetNext(i, prev[i]->GetNext(i));
    prev[i]->SetNext(i, insert_node);
  }
  return true;
}

template <typename Key, class Comparator>
auto SkipList<Key, Comparator>::FindPrevNodes(const Key &key, std::vector<SkipListNode *> &prev) -> bool {
  SkipListNode *cur_node = &head_;
  for (int i = max_height_ - 1; i >= 0; i--) {
    while (cur_node->GetNext(i) && cur_node->GetNext(i)->GetKey() < key) {
      cur_node = cur_node->GetNext(i);
    }
    prev[i] = cur_node;
  }
  return true;
}

template <typename Key, class Comparator>
auto SkipList<Key, Comparator>::Delete(const Key &key) -> bool {
  std::vector<SkipListNode *> prev(MaxHeight);
  if (!FindPrevNodes(key, prev)) {
    return false;
  }

  SkipListNode *delete_node = prev[0]->GetNext(0);
  assert(delete_node->GetKey() == key);

  SkipListNode *prev_node = nullptr;
  for (int i = 0; i < delete_node->GetSize(); i++) {
    prev_node = prev[i];
    prev_node->SetNext(i, delete_node->GetNext(i));
  }

  delete delete_node;
  return true;
}

// Explicit instantiation
template class SkipList<int, KeyComparator<int>>;

} // namespace skiplist
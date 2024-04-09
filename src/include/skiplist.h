#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include "comparator.h"

namespace skiplist {

const int MaxHeight = 12;

template<typename Key, class Comparator>
class SkipList {
public:
  /*****************************************************
                 SkipList node abstraction
  ******************************************************/
  class SkipListNode {
  public:
    explicit SkipListNode() {
      next_.resize(1);
    }
    explicit SkipListNode(Key key);
    explicit SkipListNode(Key key, int level);

    ~SkipListNode() = default;
    
    void SetNext(int n, SkipListNode *next);
    auto GetNext(int n) -> SkipListNode *;
    void SetKey(const Key &key) { key_ = key; }
    auto GetKey() -> Key { return key_; }

    void Resize(int size) { next_.resize(size); }
    auto GetSize() const -> int { return next_.size(); }

  private:
    Key key_;
    std::vector<SkipListNode *> next_;
  };

  explicit SkipList(Comparator cmp);
  ~SkipList() = default;

  // disable potential copy
  SkipList(const SkipList &other) = delete;
  auto operator=(const SkipList &) -> SkipList & = delete;

  /**
   * Find a node in skip list.
   * @param key key to find
   * @param[out] node return a found node, nullptr if can't find
   * @return true if the delete is successful
   */
  auto Find(const Key &key, SkipListNode *node) -> bool;

  /**
   * Insert a node into skip list.
   * @param key key to insert
   * @return true if the insert is successful (i.e. there is enough space)
   */
  auto Insert(const Key &key) -> bool;

  /**
   * Helper function of insert, assume there is no duplicate key.
   * @param key key to insert
   * @return true if the insert is successful (i.e. there is enough space)
   */
  auto FindPrevNodes(const Key &key, std::vector<SkipListNode *> &prev) -> bool;


  /**
   * Delete a node into skip list.
   * @param key key to delete
   * @return true if the delete is successful
   */
  auto Delete(const Key &key) -> bool;

  /**
   * Helper function
   */
  auto GetMaxHeight() const -> int { return max_height_; }

  auto RandomHeight() const -> int {
    int level = 1;
    while (rand() % 2 && level < MaxHeight) {
      level++;
    }
    return level;
  }

  // below are used for debug
  void AppendNode(SkipListNode *add_node) {
    SkipListNode *node = &head_;
    while (node->GetNext(0) != nullptr) {
      node = node->GetNext(0);
    }
    node->SetNext(0, add_node);
  }

  auto NewNode(Key key) -> SkipListNode * {
    return new SkipListNode(key);
  }

  void PrintSkipList() {
    SkipListNode *node = &head_;
    while (node->GetNext(0) != nullptr) {
      std::cout << "Node: " <<  node->GetKey() << " size: " << node->GetSize() << std::endl;
      node = node->GetNext(0);
    }
    std::cout << "Node: " <<  node->GetKey() << " size: " << node->GetSize() << std::endl;
  }

private:
  Comparator cmp_;       // comparator used to compare any type
  SkipListNode head_;   // head node of skip list
  int max_height_{1};       // store the current max height of skip list
};

} // namespace skiplist

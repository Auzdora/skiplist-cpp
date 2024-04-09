
namespace skiplist {

template <typename Type>
class Comparator {
public:
  virtual int compare(const Type &lhs, const Type &rhs) = 0;

};

template <typename Key>
class KeyComparator : Comparator<Key> {
  int compare(const Key &lhs, const Key &rhs) override {
    if (lhs > rhs) {
        return 1;
    } else if (lhs < rhs) {
        return -1;
    }
    return 0;
  }
};

} // namespace skiplist
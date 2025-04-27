#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : kCapacity(capacity), right_(capacity), buffer_(capacity, 0) {}

  bool Empty() const { return (right_ == kCapacity); }

  size_t Size() const {
    if (Empty()) {
      return 0;
    }
    if (right_ >= left_) {
      return right_ - left_ + 1;
    }
    return right_ + 1 + kCapacity - left_;
  }

  bool TryPush(int element) {
    if (Size() == kCapacity) {
      return false;
    }
    if (Empty()) {
      left_ = 0;
      right_ = 0;
    } else {
      right_ = (right_ + 1) % kCapacity;
    }
    buffer_[right_] = element;
    return true;
  }

  bool TryPop(int* element) {
    if (Empty()) {
      return false;
    }
    int value = buffer_[left_];
    *element = value;
    buffer_[left_] = 0;
    if (left_ == right_) {
      left_ = 0;
      right_ = kCapacity;
    } else {
      left_ = (left_ + 1) % kCapacity;
    }
    return true;
  }

 private:
  const size_t kCapacity;
  std::vector<int> buffer_;
  size_t left_ = 0;
  size_t right_ = 0;
};

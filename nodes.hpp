#import <functional>

class SinglyLinkedNodeHooks {
public:
  static std::function<void()> onNew;
  static std::function<void()> onDelete;

  static void reset() {
    onNew = NULL;
    onDelete = NULL;
  }
};

#ifndef INIT_NODE_HOOKS
#define INIT_NODE_HOOKS 1
std::function<void()> SinglyLinkedNodeHooks::onNew = NULL;
std::function<void()> SinglyLinkedNodeHooks::onDelete = NULL;
#endif

template <typename T>
class SinglyLinkedNode {
public:
  T data;
  SinglyLinkedNode<T>* reference;

  SinglyLinkedNode<T>() {
    reference = NULL;
  }

  void* operator new(size_t size) {
    if (SinglyLinkedNodeHooks::onNew != NULL) {
      SinglyLinkedNodeHooks::onNew();
    }
    return ::operator new(size);
  }

  void operator delete(void* p) {
    if (SinglyLinkedNodeHooks::onDelete != NULL) {
      SinglyLinkedNodeHooks::onDelete();
    }
    ::operator delete(p);
  }
};

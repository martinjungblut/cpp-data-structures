#import <functional>
#import <iostream>

#ifndef SINGLY_LINKED_NODE_HOOKS
#define SINGLY_LINKED_NODE_HOOKS 1
class SinglyLinkedNodeHooks {
public:
  inline static std::function<void()> onNew = NULL;
  inline static std::function<void()> onDelete = NULL;

  static void reset() {
    onNew = NULL;
    onDelete = NULL;
  }
};
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

#ifndef DOUBLY_LINKED_NODE_HOOKS
#define DOUBLY_LINKED_NODE_HOOKS 1
class DoublyLinkedNodeHooks {
public:
  inline static std::function<void()> onNew = NULL;
  inline static std::function<void()> onDelete = NULL;

  static void reset() {
    onNew = NULL;
    onDelete = NULL;
  }
};
#endif

template <typename T>
class DoublyLinkedNode {
public:
  T data;
  DoublyLinkedNode<T>* previous;
  DoublyLinkedNode<T>* next;

  DoublyLinkedNode<T>() {
    previous = NULL;
    next = NULL;
  }

  void* operator new(size_t size) {
    if (DoublyLinkedNodeHooks::onNew != NULL) {
      DoublyLinkedNodeHooks::onNew();
    }
    return ::operator new(size);
  }

  void operator delete(void* p) {
    if (DoublyLinkedNodeHooks::onDelete != NULL) {
      DoublyLinkedNodeHooks::onDelete();
    }
    ::operator delete(p);
  };

  template <typename TT>
  friend std::ostream& operator<<(std::ostream&, const DoublyLinkedNode<TT>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const DoublyLinkedNode<T>& node) {
  return stream << " data: " << node.data << " previous: " << node.previous << " next: " << node.next << " addr: " << &node;
}

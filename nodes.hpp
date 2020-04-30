template <typename T>
class SinglyLinkedNode {
public:
  T data;
  SinglyLinkedNode<T>* reference;

  SinglyLinkedNode<T>() {
    reference = NULL;
  }
};

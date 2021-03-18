#ifndef QUEUE_HPP_
#define QUEUE_HPP_

template <typename T>
class Queue
{
  public:
    class Node;
    std::shared_ptr<Node> head = nullptr;

    class Node
    {
      public:
        int data;
        std::shared_ptr<Node> fore_ptr;

        std::shared_ptr<Node> newNode(T x)
        {
          std::shared_ptr<Node> N = std::make_shared<Node>();
          N->data = x;
          N->fore_ptr = nullptr;
          return N;
        }
    };

    void enqueue(const T& newElement);
    T dequeue();
};

template <typename T>
void Queue<T>::enqueue(const T& newElement)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);
  if(head == nullptr)
  {
    head = temp_ptr;
  } else
  {
    std::shared_ptr<Node> search_ptr(nullptr);
    search_ptr = head;
      
    while (search_ptr->fore_ptr != nullptr)
    {
      search_ptr = search_ptr->fore_ptr;
    }
    
    search_ptr->fore_ptr = temp_ptr;

    search_ptr = nullptr;
  }
  temp_ptr = nullptr;
}

template <typename T>
T Queue<T>::dequeue()
{
  T dequeue_value;

  if(head == nullptr)
  {
    std::cerr << "Queue is empty!\n";
    exit(1);
  }

  dequeue_value = head->data;
  
  head = head->fore_ptr;

  return dequeue_value;
}

#endif /* QUEUE_HPP_ */

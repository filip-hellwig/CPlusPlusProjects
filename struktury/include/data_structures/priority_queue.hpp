#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

template <typename T>
class PriorityQueue
{
  public:
    class Node;
    std::shared_ptr<Node> head = nullptr;
    int num_nodes;

    PriorityQueue()
    {
      num_nodes = 0;
    }

    class Node
    {
      public:
        int data;
        int priority;
        std::shared_ptr<Node> fore_ptr;
        std::shared_ptr<Node> back_ptr;

        std::shared_ptr<Node> newNode(T x, int p)
        {
          std::shared_ptr<Node> N = std::make_shared<Node>();
          N->data = x;
          N->priority = p;
          N->fore_ptr = nullptr;
          N->back_ptr = nullptr; 
          return N;
        }
    };

    void enqueue(const T& newElement, int priority);
    T dequeue();
};


template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int prio)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement, prio);
  if(head == nullptr)
  {
    head = temp_ptr;
  } else
  {
    std::shared_ptr<Node> search_ptr(nullptr);
    search_ptr = head;
    int iter_num = 0;
      
    for(int i = 0; i < num_nodes-1 && temp_ptr->priority <= search_ptr->priority; i++)
    {
      search_ptr = search_ptr->fore_ptr; 
      iter_num++;
    }
    
    if (iter_num == num_nodes-1 && temp_ptr->priority <= search_ptr->priority)
    {
      search_ptr->fore_ptr = temp_ptr;
      temp_ptr->back_ptr = search_ptr;
    } else if (iter_num == 0)
    {
      head->back_ptr = temp_ptr;
      temp_ptr->fore_ptr = head;
      head = temp_ptr;
    } else
    {
      temp_ptr->fore_ptr = search_ptr;
      temp_ptr->back_ptr = search_ptr->back_ptr;
      search_ptr->back_ptr = temp_ptr;
      temp_ptr->back_ptr->fore_ptr = temp_ptr;
    }
    search_ptr = nullptr;
  }
  temp_ptr = nullptr;
  num_nodes++;
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
  T dequeue_value;

  if(head == nullptr)
  {
    std::cerr << "Queue is empty!\n";
    exit(1);
  }

  dequeue_value = head->data;
  
  head = head->fore_ptr;

  num_nodes--;

  return dequeue_value;
}

#endif /* PRIORITY_QUEUE_HPP_ */

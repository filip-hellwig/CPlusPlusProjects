#ifndef QUEUE_HPP_
#define QUEUE_HPP_

template <typename T>
class Queue
{
  public:
    class Node;     // deklaracja klasy Node
    std::shared_ptr<Node> head = nullptr;      // wskazuje na pierwszy element kolejki

    class Node
    {
      public:
        int data;       // przechowuje dane
        std::shared_ptr<Node> fore_ptr;       // wskaźnik na kolejny element

        std::shared_ptr<Node> newNode(T x)      // tworzymy nowy węzeł, zwracamy wskaźnik na niego
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
void Queue<T>::enqueue(const T& newElement)     // funkcja wstawiająca element na koniec kolejki
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);      // wskaźnik trzymający nowy węzeł
  if(head == nullptr)     // sprawdzamy czy kolejka jest pusta
  {
    head = temp_ptr;
  } else
  {   
    std::shared_ptr<Node> search_ptr(nullptr);      // wskaźnik iterujący po liście
    search_ptr = head;
      
    while (search_ptr->fore_ptr != nullptr)     // szukamy ostatniego elementu listy
    {
      search_ptr = search_ptr->fore_ptr;
    }
    
    search_ptr->fore_ptr = temp_ptr;

    search_ptr = nullptr;
  }
  temp_ptr = nullptr;
}

template <typename T>
T Queue<T>::dequeue()       // funkcja usuwająca element z początku kolejki
{
  T dequeue_value;

  if(head == nullptr)     // sprawdzamy czy jest coś w kolejce
  {
    std::cerr << "Queue is empty!\n";
    exit(1);
  }

  dequeue_value = head->data;
  
  head = head->fore_ptr;

  return dequeue_value;
}

#endif /* QUEUE_HPP_ */

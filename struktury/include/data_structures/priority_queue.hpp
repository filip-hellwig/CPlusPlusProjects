#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

template <typename T>
class PriorityQueue
{
  public:
    class Node;     // deklarujemy klasę node
    std::shared_ptr<Node> head = nullptr;     // wskaźnik na pierwszy element listy
    int num_nodes;      // przechowuje informację o ilości elementów

    PriorityQueue()
    {
      num_nodes = 0;
    }

    class Node
    {
      public:
        int data;     // przechowuje dane
        int priority;     // przechowuje wielkość priorytetu
        std::shared_ptr<Node> fore_ptr;     // wskaźnik na kolejny element
        std::shared_ptr<Node> back_ptr;     // wskaźnik na poprzedni element

        std::shared_ptr<Node> newNode(T x, int p)     // tworzymy nowy węzeł, zwracamy wskaźnik na niego
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


// funkcja wstawiająca nowy element w odpowiednim miejscu kolejki. Elementy o najwyższym priorytecie są na początku,
// elementy o niższym na końcu. Elementy są wstawiane według priorytetu.
template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int prio)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement, prio);      // wskaźnik na nowy węzeł
  if(head == nullptr)       // sprawdzamy czy jest jakiś element w kolejce
  {
    head = temp_ptr;
  } else
  {
    std::shared_ptr<Node> search_ptr(nullptr);      // wskaźnik służący do iterowania po kolejce
    search_ptr = head;
    int iter_num = 0;     // liczy ilość iteracji

    // szukamy odpowiedniego miejsca dla elementu (porównujemy proprytety, szukamy mniejszego)
    for(int i = 0; i < num_nodes-1 && temp_ptr->priority <= search_ptr->priority; i++)      
    {
      search_ptr = search_ptr->fore_ptr; 
      iter_num++;
    }
    
    if (iter_num == num_nodes-1 && temp_ptr->priority <= search_ptr->priority)      // wstawiamy na koniec listy (koniec kolejki)
    {
      search_ptr->fore_ptr = temp_ptr;
      temp_ptr->back_ptr = search_ptr;
    } else if (iter_num == 0)     // wstawiemy na początek kolejki (element ma najwyższy priorytet)
    {
      head->back_ptr = temp_ptr;
      temp_ptr->fore_ptr = head;
      head = temp_ptr;
    } else      // wstawiamy w środek kolejki, w odpowiednie miejsce
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
T PriorityQueue<T>::dequeue()     // usuwamy element z początku kolejki
{
  T dequeue_value;

  if(head == nullptr)     // sprawdzamy czy kolejka jest pusta
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

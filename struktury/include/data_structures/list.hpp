#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

template <typename T>
class List
{
  public:
    class Node;     // deklaracja klasy node
    std::shared_ptr<Node> head = nullptr;     // wskazuje na pierwszy element listy
    int num_nodes;      // liczy ilość węzłów w liście

    List()
    {
      num_nodes = 0;
    }

    class Node
    {
      public:
        T data;     // przechowuje dane
        std::shared_ptr<Node> fore_ptr;     // wskaźnik na kolejny element
        std::shared_ptr<Node> back_ptr;     // wskaźnik na poprzedni element

        std::shared_ptr<Node> newNode(T x)      // tworzymy nowy węzeł, zwracamy wskaźnik na niego
        {
          std::shared_ptr<Node> N = std::make_shared<Node>();
          N->data = x;
          N->fore_ptr = nullptr;
          N->back_ptr = nullptr;
          return N;
        }
    };



    class Iterator
    {
      public:
        using difference_type = long;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(std::shared_ptr<Node> newNode = nullptr);

        Iterator operator++();
        Iterator operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        difference_type operator-(const Iterator& other) const;
        Iterator operator+(difference_type diff) const;
        Iterator operator-(difference_type diff) const;
        Iterator operator[](std::size_t index);
        T& operator*();
        
      private:
        std::shared_ptr<Node> node_ptr = nullptr;
    };

    class ConstIterator
    {
    public:
      using difference_type = long;
      using value_type = T;
      using pointer = const T*;
      using reference = const T&;
      using iterator_category = std::random_access_iterator_tag;

      ConstIterator(std::shared_ptr<Node> newNode = nullptr);

      ConstIterator operator++();
      ConstIterator operator--();
      bool operator==(const ConstIterator& other) const;
      bool operator!=(const ConstIterator& other) const;
      bool operator>(const ConstIterator& other) const;
      bool operator<(const ConstIterator& other) const;
      difference_type operator-(const ConstIterator& other) const;
      ConstIterator operator+(difference_type diff) const;
      ConstIterator operator-(difference_type diff) const;
      ConstIterator operator[](std::size_t index);
      const T& operator*();

    private:
      std::shared_ptr<Node> node_ptr = nullptr;
    };

    void pushBack(const T& newElement);
    void pushFront(const T& newElement);
    void insert(const T& newElement, int index);
    void remove(const T& element);
    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    T& operator[](int index);
};

template <typename T>
List<T>::Iterator::Iterator(std::shared_ptr<Node> newNode)
{
  node_ptr = newNode;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{
  node_ptr = node_ptr->fore_ptr;
  return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
  node_ptr = node_ptr->back_ptr;
  return *this;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  return node_ptr == other.node_ptr;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  return node_ptr != other.node_ptr;
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& other) const
{
  Iterator iter(node_ptr);
  for(int i=0; iter.node_ptr != nullptr; i++)     // ta pętla sprawdza czy węzeł other jest dalej w liście niż this
  {
    if(iter == other)
    {
      return false;
    }
    ++iter;
  }
  return true;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& other) const
{
  Iterator iter(node_ptr);
  for(int i=0; iter.node_ptr != nullptr; i++)     // ta pętla sprawdza czy węzeł other jest dalej w liście niż this
  {
    if(iter == other)
    {
      return true;
    }
    ++iter;
  }
  return false;
}

template <typename T>
typename List<T>::Iterator::difference_type List<T>::Iterator::operator-(const Iterator& other) const
{
  int diff_value = 0;

  Iterator iter{*this > other ? other.node_ptr : node_ptr};
  Iterator iterEnd{*this > other ? node_ptr : other.node_ptr};

  for(; iter != iterEnd; diff_value++, ++iter)
  {
  }
     
  return diff_value;
  
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(difference_type diff) const
{
  Iterator iter(node_ptr);
  for(int i=0; i < diff; i++)
  {
    ++iter;
  }
  return Iterator(iter.node_ptr);
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(difference_type diff) const
{
  Iterator iter(node_ptr);
  for(int i=0; i < diff; i++)
  {
    --iter;
  }
  return Iterator(iter.node_ptr);
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator[](std::size_t index)
{
  Iterator iter(node_ptr);

  if(index == 0)
  {
    return Iterator(iter.node_ptr);
  } else if(index > 0)
  {
    for(int i=0; i < index; i++)
    {
      ++iter;
    }
    return Iterator(iter.node_ptr);
  } else
  {
    for(int i=0; i > index; i--)
    {
      --iter;
    }
    return Iterator(iter.node_ptr);
  }
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    static T element;
    return element = node_ptr->data;
}





template <typename T>
List<T>::ConstIterator::ConstIterator(std::shared_ptr<Node> newNode)
{
  node_ptr = newNode;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++()
{
  node_ptr = node_ptr->fore_ptr;
  return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
  node_ptr = node_ptr->back_ptr;
  return *this;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
{
  return node_ptr == other.node_ptr;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
  return node_ptr != other.node_ptr;
}

template <typename T>
bool List<T>::ConstIterator::operator>(const ConstIterator& other) const
{
  ConstIterator iter(node_ptr);
  for(int i=0; iter.node_ptr != nullptr; i++)     // ta pętla sprawdza czy węzeł other jest dalej w liście niż this
  {
    if(iter == other)
    {
      return false;
    }
    ++iter;
  }
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator<(const ConstIterator& other) const
{
  ConstIterator iter(node_ptr);
  for(int i=0; iter.node_ptr != nullptr; i++)     // ta pętla sprawdza czy węzeł other jest dalej w liście niż this
  {
    if(iter == other)
    {
      return true;
    }
    ++iter;
  }
  return false;
}

template <typename T>
typename List<T>::ConstIterator::difference_type List<T>::ConstIterator::operator-(const ConstIterator& other) const
{
  int diff_value = 0;

  ConstIterator iter{*this > other ? other.node_ptr : node_ptr};
  ConstIterator iterEnd{*this > other ? node_ptr : other.node_ptr};

  for(; iter != iterEnd; diff_value++, ++iter)
  {
  }

  return diff_value;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator+(difference_type diff) const
{
  ConstIterator iter(node_ptr);
  for(int i=0; i < diff; i++)
  {
    ++iter;
  }
  return ConstIterator(iter.node_ptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator-(difference_type diff) const
{
  ConstIterator iter(node_ptr);
  for(int i=0; i < diff; i++)
  {
    --iter;
  }
  return ConstIterator(iter.node_ptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator[](std::size_t index)
{
  ConstIterator iter(node_ptr);

  if(index == 0)
  {
    return ConstIterator(iter.node_ptr);
  } else if(index > 0)
  {
    for(int i=0; i < index; i++)
    {
      ++iter;
    }
    return ConstIterator(iter.node_ptr);
  } else
  {
    for(int i=0; i > index; i--)
    {
      --iter;
    }
    return ConstIterator(iter.node_ptr);
  }
}

template <typename T>
const T& List<T>::ConstIterator::operator*()
{
  static T element;
  return element = node_ptr->data;
}









template <typename T>
void List<T>::pushBack(const T& newElement)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);      //wskaźnik na nowy węzeł
  if(head == nullptr)     //sprawdzamy czy lista ma jakiś element
  {
    head = temp_ptr;
  } else
  {
    std::shared_ptr<Node> search_ptr(nullptr);      // wskaźnik używany do szukania
    search_ptr = head;
      
    while (search_ptr->fore_ptr != nullptr)     // szukamy ostatniego węzła listy
    {
      search_ptr = search_ptr->fore_ptr;
    }
    
    search_ptr->fore_ptr = temp_ptr;      // wstawiamy nowy węzeł na końcu listy
    temp_ptr->back_ptr = search_ptr;

    search_ptr = nullptr;
  }
  temp_ptr = nullptr;
  num_nodes++;
}

template <typename T>
void List<T>::pushFront(const T& newElement)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);      // wskaźnik na nowy węzeł
  if(head == nullptr)     //sprawdzamy czy lista ma jakiś element
  {
    head = temp_ptr;
  } else
  {
    head->back_ptr = temp_ptr;      // dodajemy węzeł na początku listy
    temp_ptr->fore_ptr = head;
    head = temp_ptr;
  }
  temp_ptr = nullptr;
  num_nodes++;
}

template <typename T>
void List<T>::insert(const T& newElement, int index)
{
  if(index == 0)      // dodajemy na początku listy
  {
    pushFront(newElement);
  } else if (index == num_nodes)      // dodajemy na końcu listy
  {
    pushBack(newElement);
  } else if (index < 0 || index > num_nodes)      // sprawdzam, czy index jest dobry
  {
    std::cerr << "Index is inwalid!\n";
    exit(1);
  } else
  {
    Node node;
    std::shared_ptr<Node> temp_ptr = node.newNode(newElement);      // wskaźnik na nowy węzeł
    if(head == nullptr)     //sprawdzamy czy lista ma jakiś element
    {
      head = temp_ptr;
    } else
    {
      std::shared_ptr<Node> search_ptr(nullptr);      // wskaźnik używany do szukania węzła index-1
      search_ptr = head;
        
      for(int i = 0; i < index-1; i++)
      {
        search_ptr = search_ptr->fore_ptr;
      }
      
      temp_ptr->back_ptr = search_ptr;      // wstawiamy nowy węzeł pomiędzy dwoma już istniejącymy
      temp_ptr->fore_ptr = search_ptr->fore_ptr;
      temp_ptr->fore_ptr->back_ptr = temp_ptr;
      search_ptr->fore_ptr = temp_ptr;

      search_ptr = nullptr;
    }
    temp_ptr = nullptr;
    num_nodes++;
  }
}

template <typename T>
void List<T>::remove(const T& element)
{
  std::shared_ptr<Node> search_ptr(nullptr);      // wskaźnik szukający elementu do usunięcia
  int finish = 0;     // flaga do kończenia usuwania

  while(finish != 1)      // dopóki flaga jest 0, szukamy wszystkich elementów do usunięcia
  {
    search_ptr = head;
    int iter_num = 0;     // sprawdza ile elementów przeszliśmy, pilnuje wyjścia za listę

    for(int i = 0; i < num_nodes && search_ptr->data != element; i++)       // szukamy elementu, jeżeli w ogóle istnieje
    {
      search_ptr = search_ptr->fore_ptr;
      iter_num++;
    }

    if(iter_num == 0)     // search w ogóle nie iterował, to usuwamy pierwszy element
    {
      head = search_ptr->fore_ptr;
      search_ptr->fore_ptr->back_ptr = search_ptr->back_ptr;
      search_ptr->back_ptr = nullptr;
      search_ptr->fore_ptr = nullptr;
      num_nodes--;
    } else if (iter_num == num_nodes-1)     // jeżeli search iterował po całej liście, ale skończył, to usuwamy ostatni element
    {
      search_ptr->back_ptr->fore_ptr = search_ptr->fore_ptr;
      search_ptr->back_ptr = nullptr;
      search_ptr->fore_ptr = nullptr;
      num_nodes--;
    } else if (iter_num == num_nodes)     // jeżeli search interował po całej liście, ale się nie zatrzymał, to kończymy funkcję
    {
      finish = 1;     // flaga do zakończenia while-a
      search_ptr = nullptr;
      return;
    } else      // jeżeli search iterował inną ilość razy, to usuwamy element ze środka listy
    {
      search_ptr->back_ptr->fore_ptr = search_ptr->fore_ptr;
      search_ptr->fore_ptr->back_ptr = search_ptr->back_ptr;
      search_ptr->back_ptr = nullptr;
      search_ptr->fore_ptr = nullptr;
      num_nodes--;
    }
  }
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
  return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end()
{
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{

    return ConstIterator(head);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
    return ConstIterator(nullptr);
}

template <typename T>
T& List<T>::operator[](int index)
{
  static T element;

  if(index < 0 || index >= num_nodes)     // sprawdzamy czy taki element istnieje
  {
    std::cerr << "This index is invalid!\n";
    exit(1);
  }

  std::shared_ptr<Node> temp_ptr(nullptr);      // wskaźnik służy do szukania elementu
  temp_ptr = head;

  for(int i = 0; i < index; i++)      // iterujemy aż do znalezienia elementu
  {
    temp_ptr = temp_ptr->fore_ptr;
  }
  element = temp_ptr->data;
  temp_ptr = nullptr;

  return element;
}

#endif /* LIST_HPP_ */

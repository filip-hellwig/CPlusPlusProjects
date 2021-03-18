#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

template <typename T>
class List
{
  public:
    class Node;
    std::shared_ptr<Node> head = nullptr;
    int num_nodes;

    List()
    {
      num_nodes = 0;
    }

    class Node
    {
      public:
        T data;
        std::shared_ptr<Node> fore_ptr;
        std::shared_ptr<Node> back_ptr;

        std::shared_ptr<Node> newNode(T x)
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

        Iterator(Node* node = nullptr);

        Iterator operator++();
        Iterator operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        difference_type operator-(const Iterator& other) const;
        Iterator operator+(difference_type diff) const;
        Iterator operator-(difference_type diff) const;
        Iterator operator[](std::size_t i);
        T& operator*();
    };

    class ConstIterator
    {
    public:
      using difference_type = long;
      using value_type = T;
      using pointer = const T*;
      using reference = const T&;
      using iterator_category = std::random_access_iterator_tag;

      ConstIterator(Node* node = nullptr);

      ConstIterator operator++();
      ConstIterator operator--();
      bool operator==(const ConstIterator& other) const;
      bool operator!=(const ConstIterator& other) const;
      bool operator>(const ConstIterator& other) const;
      bool operator<(const ConstIterator& other) const;
      difference_type operator-(const ConstIterator& other) const;
      ConstIterator operator+(difference_type diff) const;
      ConstIterator operator-(difference_type diff) const;
      ConstIterator operator[](std::size_t i);
      const T& operator*();
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
List<T>::Iterator::Iterator(typename List<T>::Node* node)
{
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
  // TODO: implement
  return Iterator();
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
typename List<T>::Iterator::difference_type List<T>::Iterator::operator-(const Iterator& other) const
{
  // TODO: implement
  return 0;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator[](std::size_t i)
{
  // TODO: implement
  return Iterator();
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    // TODO: implement
    static T element;
    return element;
}





template <typename T>
List<T>::ConstIterator::ConstIterator(typename List<T>::Node* node)
{
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++()
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator>(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator<(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
typename List<T>::ConstIterator::difference_type List<T>::ConstIterator::operator-(const ConstIterator& other) const
{
  // TODO: implement
  return 0;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator+(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator-(difference_type diff) const
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator[](std::size_t i)
{
  // TODO: implement
  return Iterator();
}

template <typename T>
const T& List<T>::ConstIterator::operator*()
{
    // TODO: implement
    static T element;
    return element;
}









template <typename T>
void List<T>::pushBack(const T& newElement)
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
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);
  if(head == nullptr)
  {
    head = temp_ptr;
    num_nodes++;
  } else
  {
    head->back_ptr = temp_ptr;
    temp_ptr->fore_ptr = head;
    head = temp_ptr;
  }
  temp_ptr = nullptr;
  num_nodes++;
}

template <typename T>
void List<T>::insert(const T& newElement, int index)
{
  if(index == 0)
  {
    pushFront(newElement);
  } else if (index == num_nodes)
  {
    pushBack(newElement);
  } else if (index < 0 || index > num_nodes)
  {
    std::cerr << "Index is inwalid!\n";
    exit(1);
  } else
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
        
      for(int i = 0; i < index-1; i++)
      {
        search_ptr = search_ptr->fore_ptr;
      }
      
      temp_ptr->back_ptr = search_ptr;
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
  std::shared_ptr<Node> search_ptr(nullptr);
  search_ptr = head;
  int iter_num = 0;
  
  for(int i = 0; i < num_nodes && search_ptr->data != element; i++)
  {
    search_ptr = search_ptr->fore_ptr;
    iter_num++;
  }

  if(iter_num == 0)
  {
    head = search_ptr->fore_ptr;
    search_ptr->fore_ptr->back_ptr = search_ptr->back_ptr;
    search_ptr->back_ptr = nullptr;
    search_ptr->fore_ptr = nullptr;
    search_ptr = nullptr;
  } else if (iter_num == num_nodes-1)
  {
    search_ptr->back_ptr->fore_ptr = search_ptr->fore_ptr;
    search_ptr->back_ptr = nullptr;
    search_ptr->fore_ptr = nullptr;
    search_ptr = nullptr;
  } else if (iter_num == num_nodes)
  {
    std::cerr << "This element does not exist!\n";
    exit(1);
  } else
  {
    search_ptr->back_ptr->fore_ptr = search_ptr->fore_ptr;
    search_ptr->fore_ptr->back_ptr = search_ptr->back_ptr;
    search_ptr->back_ptr = nullptr;
    search_ptr->fore_ptr = nullptr;
    search_ptr = nullptr;
  }
  num_nodes--;
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
    // TODO: implement
    return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::end()
{
    // TODO: implement
    return Iterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{

    // TODO: implement
    return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
    return ConstIterator();
    // TODO: implement
}

template <typename T>
T& List<T>::operator[](int index)
{
  static T element;

  if(index < 0 || index >= num_nodes)
  {
    std::cerr << "This index is invalid!\n";
    exit(1);
  }

  std::shared_ptr<Node> temp_ptr(nullptr);
  temp_ptr = head;

  for(int i = 0; i < index; i++)
  {
    temp_ptr = temp_ptr->fore_ptr;
  }
  element = temp_ptr->data;
  temp_ptr = nullptr;

  return element;
}

#endif /* LIST_HPP_ */

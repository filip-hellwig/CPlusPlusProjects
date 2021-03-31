#ifndef STACK_HPP_
#define STACK_HPP_
#include <iostream>

template <typename T>
class Stack
{
  public:
    class Node;     // deklaracja klasy Node
    std::shared_ptr<Node> top = nullptr;      // wskazuje na pierwszy element stosu

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
    void push(const T& newElement);
    T pop();
};

template <typename T>
void Stack<T>::push(const T& newElement)        // dodajemy element na początek stosu
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);
  if(top == nullptr)      // sprawdzamy czy stos jest pusty
  {
    top = temp_ptr;
    return;
  }
  temp_ptr->fore_ptr = top;
  top = temp_ptr;
}

template <typename T>
T Stack<T>::pop()     // ściągamy element z kończa stosu
{
  T pop_value;

  if(top == nullptr)      // sprawdzamy czy stos nie jest pusty
  {
    std::cerr << "Stack is empty!\n";
    exit(1);
  }

  pop_value = top->data;
  top = top->fore_ptr;
  
  return pop_value;
}

#endif /* STACK_HPP_ */

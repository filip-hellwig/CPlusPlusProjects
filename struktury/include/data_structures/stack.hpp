#ifndef STACK_HPP_
#define STACK_HPP_
#include <iostream>

template <typename T>
class Stack
{
  public:
    class Node;
    std::shared_ptr<Node> top = nullptr;

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
    void push(const T& newElement);
    T pop();
};

template <typename T>
void Stack<T>::push(const T& newElement)
{
  Node node;
  std::shared_ptr<Node> temp_ptr = node.newNode(newElement);
  if(top == nullptr)
  {
    top = temp_ptr;
    return;
  }
  temp_ptr->fore_ptr = top;
  top = temp_ptr;
}

template <typename T>
T Stack<T>::pop()
{
  T pop_value;

  if(top == nullptr)
  {
    std::cerr << "Stack is empty!\n";
    exit(1);
  }

  pop_value = top->data;
  top = top->fore_ptr;
  
  return pop_value;
}

#endif /* STACK_HPP_ */

#include "catch2/catch.hpp"

#include <list>
#include <stack>
#include <queue>
#include <map>

TEST_CASE("List/pushFrontSTL")
{
    std::list<int> list;

    list.push_front(1);
    list.push_front(2);

    REQUIRE(list.front() == 2);
    REQUIRE(list.back() == 1);
}

TEST_CASE("List/pushBackSTL")
{
    std::list<int> list;

    list.push_back(1);
    list.push_back(2);

    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 2);
}

TEST_CASE("List/pushInsertSTL")
{
    std::list<int> list;
    std::list<int>::iterator it;

    list.push_back(1);
    list.push_back(2);

    it = list.begin();
    it++;

    list.insert(it, 3);
    it--;
    it--;

    list.insert(it, 4);

    it = list.begin();

    REQUIRE(*it == 4);
    it++;
    REQUIRE(*it == 1);
    it++;
    REQUIRE(*it == 3);
    it++;
    REQUIRE(*it == 2);
    it++;
}

TEST_CASE("List/removeSTL")
{
    std::list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.remove(2);

    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 3);

    list.remove(1);

    REQUIRE(list.front() == 3);
}

TEST_CASE("List/iteratorSTL")
{
    std::list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.sort();

    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 3);
}

TEST_CASE("List/ConstIteratorSTL")
{
    std::list<int> list;

    std::array<int, 3> refArray = {1, 2, 3};

    for(auto& element : refArray)
    {
        list.push_back(element);
    }

    int index = 0;
    for(auto it = list.cbegin(); it != list.cend(); ++it)
    {
        REQUIRE(*it == refArray[index++]);
    }
}

TEST_CASE("StackSTL")
{
    std::stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    REQUIRE(stack.top() == 3);
    stack.pop();
    REQUIRE(stack.top() == 2);
    stack.pop();
    REQUIRE(stack.top() == 1);
    stack.pop();

    REQUIRE(stack.empty());
}

TEST_CASE("QueueSTL")
{
    std::queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    REQUIRE(queue.front() == 1);
    queue.pop();
    REQUIRE(queue.front() == 2);
    queue.pop();
    REQUIRE(queue.front() == 3);
    queue.pop();
}

TEST_CASE("PriorityQueueSTL")
{
    std::priority_queue<int> queue;

    queue.push(1);
    queue.push(3);
    queue.push(2);
    
    REQUIRE(queue.top() == 3);
    queue.pop();
    REQUIRE(queue.top() == 2);
    queue.pop();
    REQUIRE(queue.top() == 1);
    queue.pop();
}

TEST_CASE("MapSTL")
{
    std::map<std::string, int> refHashArray;

    refHashArray.insert ( std::pair<std::string, int>("one",30) );
    refHashArray.insert ( std::pair<std::string, int>("two",5) );
    refHashArray.insert ( std::pair<std::string, int>("three",10) );

    REQUIRE(refHashArray["one"] == 30);
    REQUIRE(refHashArray["two"] == 5);
    REQUIRE(refHashArray["three"] == 10);

}
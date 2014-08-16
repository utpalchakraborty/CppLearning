#include <list>
#include <map>
#include <unordered_map>
#include <iostream>


int main()
{
    // list is a doubly linked list of elements.
    std::list<int> intList = { 1, 2, 3, 4, 5 };

    // iterating over the list is fast thru pointers.
    for(const int& i : intList)
    {
	std::cout << i << ", ";
    }
    std::cout << std::endl;

    // the above is a short form of using the 
    // iterators explicitly.

    for(std::list<int>::iterator p = intList.begin(); p != intList.end(); ++p)
    {
	std::cout << *p << ", ";
    }
    std::cout << std::endl;

    // map is an ordered set of elements.
    std::map<std::string, int> m;

    m.insert(std::make_pair<std::string, int>("One", 1));
    m.insert(std::make_pair<std::string, int>("Two", 2));
    m.insert(std::make_pair<std::string, int>("Three", 3));

    std::cout << m["Two"] << std::endl;

    // a hashmap is an unordered_map in C++
    std::map<std::string, int> u;

    u.insert(std::make_pair<std::string, int>("One", 1));
    u.insert(std::make_pair<std::string, int>("Two", 2));
    u.insert(std::make_pair<std::string, int>("Three", 3));

    std::cout << u["Two"] << std::endl;
    
    // each of these also have a multimap which basically allows more than 
    // one instance of the same key value.
}

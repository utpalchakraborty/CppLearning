#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void printVector(const std::vector<T>& v) 
{
   // has the standard iterators.
    for(const T& i : v)
    {
	std::cout << i;
    }
    std::cout << std::endl;
}

// below is a simple implementation of a find  on a simple vector.
// notice the use of the vector type in the value instead of another
// type. It returns an iterator. all algortihms work on iterators.
template<typename T>
std::vector<typename std::vector<T>::iterator> findValues(std::vector<T>& v,  T value)
{
    std::vector<typename std::vector<T>::iterator> retValue;
    for(auto p = v.begin(); p != v.end(); p++)
    {
	if(*p == value)
	{
	    retValue.push_back(p);
	}
    }
    return retValue;
} 

int main()
{
    // defining a vector with a initializer list
    std::vector<int> v = {1, 2, 3, 4, 1, 1 };
    
    printVector(v);
 
    // adding an element to the vector
    v.push_back(5);
  
    printVector(v);


    // standard library provides algorithms and a standard 
    // way to work with containers using iterators.
    // for example find_all returns an iterator.
    // sort needs an iterator etc. Following is an example of sort
    std::sort(v.begin(), v.end());

    printVector(v);

    auto results = findValues(v, 1);

    // using the for each algorithm to print out the contents.
    std::for_each(results.begin(), results.end(), [](std::vector<int>::iterator i) { std::cout << *i << std::endl; });

    // once again.
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i; });



    //vector does not provide range checking...
    //so invalid use of the index will result 
    //in nasty runtime out_of_range exceptions.
      

    // this is all good. but 
    std::vector<bool> boolVector;

    // is specialized and messed up.
    // it is implemented as a bitset 
    // everyone agrees that is a disaster


}

#include <iostream>
#include <vector>

template<typename T>
void printVector(std::vector<T> v)
{
   // has the standard iterators.
    for(const T& i : v)
    {
	std::cout << i;
    }
    std::cout << std::endl;
}

int main()
{
    // defining a vector with a initializer list
    std::vector<int> v = {1, 2, 3, 4 };
    
    printVector(v);
 
    // adding an element to the vector
    v.push_back(5);

    
    printVector(v);

    //vector does not provide range checking...
    //so invalid use of the index will result 
    //in nasty runtime out_of_range exceptions.
      


}

#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>

std::mutex v_mtx;
std::vector<int> v {1, 22, 4, 5, 6, 9, 10, -2 , -4, -7, 99};


void sortVector()
{
    // get the lock on the vector so that no one else can 
    // access it.
    std::unique_lock<std::mutex> lock { v_mtx };
    std::sort(v.begin(), v.end());

    // lock is releases automatically.
}

void printVector()
{
    // get the lock...
    // the locks can also be gotten in a deferred state to 
    // so that deadlocks cannot happen.
    std::unique_lock<std::mutex> lock { v_mtx };
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i; });
    std::cout << std::endl;
}

struct F
{
    std::vector<int>* inv;
    F(std::vector<int>* vv) { inv = vv; }

    void operator()()
	{
	    std::sort(inv->begin(), inv->end());
	}
};



int main()
{

    // declaring a thread and calling a normal function
    // that uses a global. Not particularly nice.
    std::thread sorter {sortVector};
    std::thread printer {printVector};

    sorter.join();
    printer.join();

    

    std::vector<int> another {5, 6, 2, 1, 99, 34, 78, 23 };

    // this is better now.
    F f {&another};

    std::thread t1 {f};

    t1.join();

    std::for_each(another.begin(), another.end(), [](int i) { std::cout << i; });

    std::cout << std::endl;

    
}

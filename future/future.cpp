#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <exception>

// make a function that takes some work to do
bool is_prime(int t)
{
    for(int i = 2; i < t/2; i++)
    {
	if(t % i == 0)
	{
	    return false;
	}
    }
    return true;
}

struct Data
{
    int x;
    std::promise<bool> p;
    std::future<bool> f = p.get_future();
    Data(int y) : x { y } {}
};

bool is_dataprime(Data& d)
{
    d.p.set_value(is_prime(d.x));
}

int main()
{
    try{

	// get the current time point
	std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

	int number = 444444443;
	std::future<bool> fut = std::async(is_prime, number);

	std::cout << "checking...";

	bool x = fut.get();

	std::cout << number << (x ? " is " : " is not ") << "prime" << std::endl;

	//initialize a data
	Data data {444454443};
	// check if it a prime on a thread.
	std::thread t {is_dataprime, std::ref(data) };
	bool y = data.f.get();
 
	std::cout << data.x << (y ? " is " : " is not ") << "prime" << std::endl;

	// without this join we get a core dumped. 
	t.join();

	// get the current timepoint again.
        auto t1 = std::chrono::high_resolution_clock::now();

	// cast the time difference in milliseconds.
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;

    }
    catch(const std::exception& e)
    {
	std::cout << e.what();
    }
   
    

    
}


